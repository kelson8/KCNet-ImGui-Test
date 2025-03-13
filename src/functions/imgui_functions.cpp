#include "imgui_functions.h"

// ImGui
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

// TODO Move ImGui functions for use in here.

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

/// <summary>
/// Setup ImGui
/// </summary>
void ImGuiFunctions::Main::SetupContext()
{
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
	io.Fonts->AddFontFromFileTTF("./lib/ImGui/misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);
}

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