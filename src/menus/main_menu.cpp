#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "keystates.h"
#endif

#include <d3d9.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

// Utility functions
#include "text_functions.h"
#include "text_file_functions.h"

// Test functions
#include "directx9_test.h"
// New test
#include "constructor_test.h"
// OpenGL
#include "opengl_test.h"

// Menus
//#include "../menus/main_menu.h"
#include "main_menu.h"
#include "vice_city_menu.h"

#include "test_menu1.h"
#include "test_menu2.h"

#include "text_menu.h"
#include "defines.h"

#ifdef LUA_TEST
#include "lua_menu.h"
#endif

// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
// Test macros
#define LIMIT 5

// Boolean values
// DirectX9Test

// TODO Make this file compatible with DirectX9 and OpenGL.
#ifdef _DIRECTX9
bool DirectX9Test::show_demo_window = false;
bool DirectX9Test::button1_clicked = false;
bool DirectX9Test::show_app_main_menu_bar = false;
bool DirectX9Test::toggle_text = false;
bool DirectX9Test::dark_mode = true; // I have dark mode enabled, I'll leave this to true.
bool DirectX9Test::define_test = false;
bool DirectX9Test::list_values = false;
bool DirectX9Test::display_cpp_version = false;

#endif

// OpenGLTest
bool OpenGLTest::show_demo_window = false;
//

// TODO Setup test for storing an array of pointers

// TODO Try to play around with PS3 homebrew or Nintendo Switch homebrew.



// This doesn't work
#ifdef _TEST1
/// <summary>
/// Testing vsprintf_s
/// https://www.educative.io/answers/what-is-vsprintfs-in-c
/// </summary>
/// <returns></returns>

int call_vsprintf_s(char* buffer, size_t numberOfElements, char* format)
{
	int result;
	va_list argList;
	va_start(argList, format);
	result = vsprintf_s(buffer, numberOfElements, format, argList);
	va_end(argList);
	return result;
}
#endif //_TEST1

// Enable this for test constructor once I get it fixed.
//#define _TEST1

/// <summary>
/// Main menu for the project, moved out of directx9_test.cpp.
/// </summary>
void MainMenu::Menu() {

	TextMenu* textMenu = new TextMenu();
	Defines* defines = new Defines();
#ifdef LUA_TEST
	LuaMenu* luaMenu = new LuaMenu();
#endif

	if (ImGui::Begin(defines->imgui_window_name, nullptr, ImGuiWindowFlags_MenuBar))
	{
		// Show the main menu
		// ReVC, test1, and test2.
		MainMenu::MainMenuTest();

		// Text File Functions

		// Text file functions test menu
		if (ImGui::CollapsingHeader("Text File Functions"))
		{
			textMenu->TextMainMenu();
		}

		ImGui::Separator();


#ifdef LUA_TEST

		if (ImGui::CollapsingHeader("Lua test functions"))
		{
			luaMenu->LuaMainMenu();
		}

#endif // LUA_TEST
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

			// End http test menu
		}
#endif //_TEST1
		
	}
}

void MainMenu::MainMenuTest() {
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//if (ImGui::Begin("KCNet ImGui", nullptr, ImGuiWindowFlags_MenuBar))
	//{
		
	// Constructor test, kills ImGui.
#ifdef _TEST1 // TODO Fixme
	Car car1("Ford", "Mustang", 1969);
#endif //_TEST1

		// Vice City Test (ReVC)
	VC::Menus::MainMenu();

	//-------------- Menu bar-----------//
		// Menu bar
		if (ImGui::BeginMenuBar())
		{
			//-------------- Test menu bar item -----------//
			if (ImGui::BeginMenu("Test"))
			{
#ifdef _DIRECTX9
				ImGui::MenuItem("Main menu bar", NULL, &DirectX9Test::show_app_main_menu_bar);
#else
				ImGui::Text("Not implemented in OpenGL");
#endif // _DIRECTX9
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		//-------------- Test1 header -----------//
		// Run the test1 menu
		TestMenu1 testMenu1 = TestMenu1();
		testMenu1.TestMenu();

		ImGui::Separator();


		//-------------- Test2 header -----------//
		TestMenu2 testMenu2 = TestMenu2();
		testMenu2.TestMenu();



}

