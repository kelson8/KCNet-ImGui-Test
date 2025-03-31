//#include "pch.h"

// https://stackoverflow.com/questions/22744262/cant-call-stdmax-because-minwindef-h-defines-max
// Fix for std::min and std::max
#define NOMINMAX

#include <string>
#include <iostream>

#include "imgui_functions.h"



// ImGui
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

#ifdef _WIN32
// For _getcwd
#include <direct.h>
#endif

//-------------- ImGui Directories -------------/

// TODO Make this work on Linux and Windows

std::string
ImGuiFunctions::Folders::GetCurrentWorkingDirectory()
{
#ifdef _WIN32
    char buffer[MAX_PATH];
    if (_getcwd(buffer, sizeof(buffer)) != nullptr) {
        return std::string(buffer);
    }
    else {
        return ""; // Or handle the error appropriately
    }
#endif
}


void
ImGuiFunctions::Folders::OpenCurrentDirectoryButton(const char* buttonLabel)
{
#ifdef _WIN32
    std::string currentDir = GetCurrentWorkingDirectory();
    if (!currentDir.empty() && ImGui::Button(buttonLabel)) 
    { 
        ShellExecuteA(nullptr, "explore", currentDir.c_str(), nullptr, nullptr, SW_SHOWNORMAL); 
    }

#endif
}

void
ImGuiFunctions::Folders::OpenDirectoryButton(std::string folder, const char* buttonLabel)
{
    //Defines defines = Defines();
#ifdef _WIN32
    // std::string currentDir = GetCurrentWorkingDirectory() + folder;
    if (!folder.empty() && ImGui::Button(buttonLabel)) {
        // Leftover log function, ReVC
        //LogFunctions::LogInfo(defines.logFile, "Folder path: " + folder);
        // ShellExecuteA(nullptr, "explore", currentDir.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
        ShellExecuteA(nullptr, "explore", folder.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    }
#endif
}



//-------------- End ImGui Directories -------------/

//-------------- ImGui input -------------/


void
ImGuiFunctions::Input::InputIntMax(const char* label, int* v, int step, int step_fast, int max_value)
{
    if (ImGui::InputInt(label, v, step, step_fast)) {
        *v = std::min(*v, max_value);
        //return true; // Value changed
    }
    //return false; // Value unchanged
}

// If you also need to set a min value, use this function instead:
void
ImGuiFunctions::Input::InputIntClamp(const char* label, int* v, int step, int step_fast, int min_value, int max_value)
{
    if (ImGui::InputInt(label, v, step, step_fast)) {
        *v = std::max(min_value, std::min(*v, max_value));
        //return true; // Value changed
    }
    //return false; // Value unchanged
}

//-------------- End ImGui input -------------/


//-------------- ImGui Window handling -------------/

/// <summary>
/// Destory the ImGui window
/// </summary>
/// <param name="hwnd"></param>
/// <param name="wc"></param>
void ImGuiFunctions::Main::DestroyWindow(HWND hwnd, WNDCLASSEXW wc)
{
	::DestroyWindow(hwnd);
	::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

/// <summary>
/// Shutdown ImGui
/// </summary>
void ImGuiFunctions::Main::ShutDown()
{
	// Shutdown ImGui
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	// Destroy ImGui Context
	ImGui::DestroyContext();
}

/// <summary>
/// Show the ImGui Window
/// </summary>
/// <param name="hwnd"></param>
void ImGuiFunctions::Main::ShowWindow(HWND hwnd)
{
	// Show the window
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);
}

// imgui_demo line 256
// TODO What's this for? Seems like it's not needed
//static void ImGuiFunctions::Main::ShowWindow(bool* p_open)
//{
//	static bool show_main_menu = false;
//
//	if (show_main_menu)
//	{
//		if (ImGui::Begin("Test"))
//		{
//			ImGui::Text("Hello World!");
//		}
//	}
//
//	if (!ImGui::Begin("Test", p_open))
//	{
//
//		ImGui::End();
//		return;
//	}
//}

//-------------- End ImGui Window handling -------------/


//-------------- ImGui Setup and fonts -------------/

/// <summary>
/// Setup ImGui
/// </summary>
void ImGuiFunctions::Main::SetupContext()
{
    bool oldFont = false;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	io.Fonts->AddFontDefault();

    if (oldFont) {
        io.Fonts->AddFontFromFileTTF("./lib/ImGui/misc/fonts/DroidSans.ttf", 16.0f);
    }
    else {
        // New font, from the Cheat Menu here https://github.com/user-grinch/Cheat-Menu/tree/master/resource/addon
        io.Fonts->AddFontFromFileTTF("./resources/text.ttf", 1.15f);
    }
	//

	
    // Here are some other fonts
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);
}



// Credit to user-grinch on github for the style code here.
// https://github.com/user-grinch/Cheat-Menu/blob/master/src/cheatmenu.cpp#L271-L335
void ImGuiFunctions::Main::ApplyStyle()
{
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;

    style->WindowPadding = ImVec2(8, 8);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(8, 8);
    style->FrameRounding = 5.0f;
    style->PopupRounding = 5.0f;
    style->ItemSpacing = ImVec2(7, 7);
    style->ItemInnerSpacing = ImVec2(7, 7);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 12.0f;
    style->ScrollbarRounding = 10.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->ChildBorderSize = 0;
    style->WindowBorderSize = 0;
    style->FrameBorderSize = 0;
    style->TabBorderSize = 0;
    style->PopupBorderSize = 0;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.33f, 0.3f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.12f, 0.12f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.12f, 0.12f, 0.12f, 0.94f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.5f, 0.5f, 0.5f, 0.3f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.7f, 0.7f, 0.7f, 0.3f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.9f, 0.9f, 0.9f, 0.3f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_Separator] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 0.95f);
    style->Colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.12f, 0.12f, 0.12f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.06f, 0.05f, 0.06f, 0.95f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.6f);
}


//-------------- End ImGui Setup and fonts -------------/

//-------------- Misc ImGui functions -------------/

/// <summary>
/// Add a help marker
/// </summary>
/// <param name="desc"></param>
static void ImGuiFunctions::Main::HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

//-------------- End Misc ImGui functions -------------/
