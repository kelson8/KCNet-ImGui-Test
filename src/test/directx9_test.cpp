#include "directx9_test.h"

// I would like to move opengl and directx into their own classes.
// So I can switch between them and the main file won't be so messy.

// This is my ImGui C++ demo, I mess around with it sometimes.

#ifndef _TEST
#define _TEST
#endif

#ifndef _DIRECTX9
//#define _DIRECTX9
#endif

#ifdef _DIRECTX9
#ifdef _TEST
// Dear ImGui: standalone example application for DirectX 9

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

// ImGui
#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "./util/keystates.h"
#endif
//

#include <d3d9.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

// Util
#include "./util/text_file_functions.h"
#include "./util/text_functions.h"
//
// Menus
#include "./menus/main_menu.h"
#include "./menus/text_menu.h"

// Enums, menu title and etc.
// TODO Move into main source folder
#include "./test/defines.h"


#include "./util/helpers.h"

// TODO Move into ../menus/http_menu.h
#include "./test/http_lib_test.h"
//

// Switch to using helpers.cpp for helper functions.
//#define _TEST2

// TODO Create src folder for project, move source files into it
// TODO Possibly create headers folder for project.

// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
// Test macros
#define LIMIT 5

// Test code
#ifndef _TEST
//#define _TEST
#endif

// Data
// TODO Move into helpers.cpp or helpers.h
#ifndef _TEST2 //!_TEST2
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};
#endif //_!_TEST2

// Forward declarations of helper functions
#ifndef _TEST2 //!_TEST2
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
#endif //!_TEST2
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void HelpMarker(const char* desc)
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

// Windows specific features
// https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c
#ifdef _WIN32
SHORT keyState = GetKeyState(VK_CAPITAL/*(caps lock)*/);
bool isToggled = keyState & 1;
bool isDown = keyState & 0x8000;
//[DllImport("kernel32.dll")]
//static extern IntPtr GetConsoleWindow();
#endif


// Will this work?

//static void setBulletText(const char* text)
//{
//	ImGui::BulletText(text);
//}
//

int test()
{
	int num1 = 5;
	int num2 = 10;

	return num1 + num2;
}

// https://www.geeksforgeeks.org/converting-number-to-string-in-cpp/
// Prints the value of 
std::string testString1()
{
	int num1 = 5;
	int num2 = 10;
	int sum = num1 + num2;
	// Convert the numbers to strings for the return value.
	std::string num1_string = std::to_string(num1);
	std::string num2_string = std::to_string(num2);
	std::string sum_string = std::to_string(sum);

	return "The value of " + num1_string + " + " + num2_string + " = " + sum_string;
}


// imgui_demo line 256
static void ShowWindow(bool* p_open)
{
	static bool show_main_menu = false;

	if (show_main_menu)
	{
		if (ImGui::Begin("Test"))
		{
			ImGui::Text("Hello World!");
		}
	}

	if (!ImGui::Begin("Test", p_open))
	{

		ImGui::End();
		return;
	}


}

static void CreateApplicationWindow()
{

}

static void InitializeD3D(HWND hwnd, WNDCLASSEXW wc)
{
	// Initialize Direct3D

#ifndef _TEST2 //!_TEST2
	if (!CreateDeviceD3D(hwnd))
#else
	if (!Helpers::CreateDeviceD3D(hwnd))
#endif //!_TEST2
	{
#ifndef _TEST2 //!_TEST2
		CleanupDeviceD3D();
#else
		Helpers::CleanupDeviceD3D();
#endif //!_TEST2
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
		//return 1;
	}


}

static void ShowWindow(HWND hwnd)
{
	// Show the window
	::ShowWindow(hwnd, SW_SHOWDEFAULT);
	::UpdateWindow(hwnd);
}

static void Render(ImVec4 clear_color)
{
#ifndef _TEST2 //!_TEST2
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
	D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
	g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
	if (g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		g_pd3dDevice->EndScene();
	}
	HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)

#else
	Helpers::g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	Helpers::g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	Helpers::g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
	D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
	Helpers::g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
	if (Helpers::g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		Helpers::g_pd3dDevice->EndScene();
	}
	HRESULT result = Helpers::g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && Helpers::g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
#endif //!_TEST2

#ifndef _TEST2 //!_TEST2
		ResetDevice();
#else
		Helpers::ResetDevice();
#endif //_TEST2
}

void setupContext()
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



// Main code

// TODO Fix this not to break when imgui_impl_glfw.cpp and imgui_impl_glfw.h is included.
// Found the fix for OpenGL here: https://github.com/ocornut/imgui/issues/1299
void DirectX9Test::directX9Test()
{

	// Define custom booleans and features.
	TextMenu *textMenu = new TextMenu();
	Defines* defines = new Defines();

#ifdef _TEST
	//std::cout << testString1();
#endif

	// Move window title into here.
	// TODO Make this grab from a enum or something.
	//const wchar_t* window_title = L"KCNet ImGui";

	// Create application window
	//ImGui_ImplWin32_EnableDpiAwareness();
	WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, defines->window_title, nullptr };
	::RegisterClassExW(&wc);
	HWND hwnd = ::CreateWindowW(wc.lpszClassName, defines->window_title, WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

	// Initialize Direct3D
	InitializeD3D(hwnd, wc);

	// Show the window
	ShowWindow(hwnd);

	// Setup Dear ImGui context
	setupContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
#ifndef _TEST2
	ImGui_ImplDX9_Init(g_pd3dDevice);
#else
	ImGui_ImplDX9_Init(Helpers::g_pd3dDevice);
#endif //!_TEST2


	// Our state
	//bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Show window
	// Main loop
	bool done = false;
	//bool button1_clicked = false;
	//bool show_app_main_menu_bar = false;
	//static bool toggle_text = false;
	//static bool dark_mode = false;
	//static bool define_test = false;
	//static bool list_values = false;

	while (!done)
	{
		// Poll and handle messages (inputs, window resize, etc.)
		// See the WndProc() function below for our to dispatch events to the Win32 backend.
		MSG msg;
		while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				done = true;
		}
		if (done)
			break;

#ifndef _TEST2
		// Handle window resize (we don't resize directly in the WM_SIZE handler)
		if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
		{
			g_d3dpp.BackBufferWidth = g_ResizeWidth;
			g_d3dpp.BackBufferHeight = g_ResizeHeight;
			g_ResizeWidth = g_ResizeHeight = 0;
#else
		if (Helpers::g_ResizeWidth != 0 && Helpers::g_ResizeHeight != 0)
		{
			Helpers::g_d3dpp.BackBufferWidth = Helpers::g_ResizeWidth;
			Helpers::g_d3dpp.BackBufferHeight = Helpers::g_ResizeHeight;
			Helpers::g_ResizeWidth = Helpers::g_ResizeHeight = 0;
#endif //!_TEST2

#ifndef _TEST2
			ResetDevice();
#else
			Helpers::ResetDevice();
#endif //!_TEST2
		}

		// Start the Dear ImGui frame
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		//MainMenu::MainMenuTest();
//#define _OLD_CODE


//***************
// Start of ImGui code
//***************
		//if (ImGui::Begin("KCNet ImGui", nullptr, ImGuiWindowFlags_MenuBar))
		if (ImGui::Begin(defines->imgui_window_name, nullptr, ImGuiWindowFlags_MenuBar))
		{
			// Show the main menu
			MainMenu::MainMenuTest();



			// Text file functions test menu
			if (ImGui::CollapsingHeader("Text File Functions"))
			{
				textMenu->TextMainMenu();
			}
			// End Text file functions test menu
			
			// HTTP Test menu, doesn't work
#ifdef _TEST1
			if (ImGui::CollapsingHeader("Http Test")) {
				bool show_html = false;
				// TODO Move this to using
				// httpTestMenu->HttpTestMainMenu();
				ImGui::Checkbox("Test", &show_html);

				if (show_html)
				{
					//ImGui::Text(HttpTest::test);
					HttpTest::test();
				}



			}
#endif //_TEST1
			// End http test menu
			

			//if (ImGui::BeginMenu("My menu"))
			//{
			//    //ImGui::BulletText("You should see this");
			//    ImGui::MenuItem("test", NULL);
			//    ImGui::EndMenu();
			//}



	}
		// End ImGui
		ImGui::End();

		ImGui::EndFrame();
//***************
// End of ImGui code
//***************

		// Rendering
		
		Render(clear_color);
}

	// Shutdown ImGui
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	// Destroy ImGui Context
	ImGui::DestroyContext();


	// Cleanup D3D Device
#ifndef _TEST2
	CleanupDeviceD3D();
#else
	Helpers::CleanupDeviceD3D();
#endif
	
	::DestroyWindow(hwnd);
	::UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

// End Main class

// Helper functions

#ifndef _TEST2
bool CreateDeviceD3D(HWND hWnd)
{
	if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
		return false;

	// Create the D3DDevice
	ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
	g_d3dpp.Windowed = TRUE;
	g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	g_d3dpp.EnableAutoDepthStencil = TRUE;
	g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
	//g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
		return false;

	return true;
}

void CleanupDeviceD3D()
{
	if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
	if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

#endif //!_TEST2

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
#ifndef _TEST2
		g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		g_ResizeHeight = (UINT)HIWORD(lParam);
#else
		Helpers::g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		Helpers::g_ResizeHeight = (UINT)HIWORD(lParam);
		
#endif //!_TEST2
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}
	return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

#endif //_TEST
#endif //_DIRECTX9