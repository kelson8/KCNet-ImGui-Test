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

// TODO Why is this here?
#ifdef _TEST
// Dear ImGui: standalone example application for DirectX 9

// Modified by kelson8, now mostly everything is separated into it's own file to make this cleaner.
// I have moved most imgui functions into imgui_functions.cpp, and most Directx stuff into helpers.cpp.
// Most of this code came from the example here:
// https://github.com/ocornut/imgui/blob/master/examples/example_win32_directx9/main.cpp

// You can use that example above for an ImGui base like I did in this project.

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
#include "text_file_functions.h"
#include "text_functions.h"
//
// Menus
#include "./menus/main_menu.h"
#include "./menus/text_menu.h"

// Enums, menu title and etc.
// TODO Move into main source folder
#include "defines.h"

#include "./util/helpers.h"

// TODO Move into ../menus/http_menu.h
#include "http_lib_test.h"
//

// Imgui functions
#include "imgui_functions.h"


// TODO Create src folder for project, move source files into it
// TODO Possibly create headers folder for project.

// TODO Get OpenGL test working and try to place it somewhere in the GZDoom game once I get it setup with CMake.

// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
// Test macros
#define LIMIT 5

// Test code
#ifndef _TEST
//#define _TEST
#endif

// Data

// TODO Test these public variables in helpers.cpp, I should be able to call this stuff like this.
LPDIRECT3D9				DirectX9Test::g_pD3D = nullptr;
LPDIRECT3DDEVICE9        DirectX9Test::g_pd3dDevice = nullptr;
UINT                     DirectX9Test::g_ResizeWidth = 0, DirectX9Test::g_ResizeHeight = 0;
D3DPRESENT_PARAMETERS    DirectX9Test::g_d3dpp = {};

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

// TODO Move these test items into a functions file, separate everything out.
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

static void CreateApplicationWindow()
{

}

static void Render(ImVec4 clear_color)
{
	DirectX9Test::g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	DirectX9Test::g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	DirectX9Test::g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
	D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
	DirectX9Test::g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
	if (DirectX9Test::g_pd3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		DirectX9Test::g_pd3dDevice->EndScene();
	}
	HRESULT result = DirectX9Test::g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && DirectX9Test::g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)

		// Moved into helpers.cpp
		Helpers::ResetDevice();
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
	Helpers::InitializeD3D(hwnd, wc);

	// Show the window
	ImGuiFunctions::Main::ShowWindow(hwnd);

	// Setup Dear ImGui context
	ImGuiFunctions::Main::SetupContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup the style from the Cheat Menu
	// https://github.com/user-grinch/Cheat-Menu
	ImGuiFunctions::Main::ApplyStyle();

	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);

#endif //!_TEST


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

		// Handle window resize (we don't resize directly in the WM_SIZE handler)
		// TODO Move this into helpers.cpp if needed.
		if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
		{
			g_d3dpp.BackBufferWidth = g_ResizeWidth;
			g_d3dpp.BackBufferHeight = g_ResizeHeight;
			g_ResizeWidth = g_ResizeHeight = 0;


			// Moved into helpers.cpp
			Helpers::ResetDevice();
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

		// Display main menu, moved into main_menu.cpp.
		MainMenu::Menu();
		// End ImGui
		ImGui::End();

		ImGui::EndFrame();


		// Rendering
		
		Render(clear_color);

//***************
// End of ImGui code
//***************
}

	// Shutdown ImGui, and destory context.
	ImGuiFunctions::Main::ShutDown();


	// Cleanup D3D Device
	// Moved into helpers.cpp
	Helpers::CleanupDeviceD3D();
	
	// Destory ImGui window
	ImGuiFunctions::Main::DestroyWindow(hwnd, wc);

}

// End Main class

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// This is required in all instances of ImGui, for the mouse and keyboard input I'm quite sure.
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
			return 0;
		DirectX9Test::g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
		DirectX9Test::g_ResizeHeight = (UINT)HIWORD(lParam);


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


#endif //_DIRECTX9
