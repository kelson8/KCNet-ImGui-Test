#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "../util/keystates.h"
#endif

#include <d3d9.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

#include "../util/text_file_functions.h"
#include "../test/directx9_test.h"
#include "../util/text_functions.h"
#include "main_menu.h"

// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
// Test macros
#define LIMIT 5

// This file is inactive, not in use yet.

// Boolean values
bool DirectX9Test::show_demo_window = true;
bool DirectX9Test::button1_clicked = false;
bool DirectX9Test::show_app_main_menu_bar = false;
bool DirectX9Test::toggle_text = false;
bool DirectX9Test::dark_mode = false;
bool DirectX9Test::define_test = false;
bool DirectX9Test::list_values = false;

//

void MainMenu::MainMenuTest() {
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	//if (ImGui::Begin("KCNet ImGui", nullptr, ImGuiWindowFlags_MenuBar))
	//{
		// Menu bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Test"))
			{
				ImGui::MenuItem("Main menu bar", NULL, &DirectX9Test::show_app_main_menu_bar);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		// Main testing header.
		if (ImGui::CollapsingHeader("test1"))
		{
			ImGui::BulletText("Hello, this should show up.");
			ImGui::Separator();

			// Menu toggle button
			if (ImGui::Button("Menu toggle"))
			{
				std::cout << "Test" << std::endl;
				// How would I check if dark mode is enabled?
				//if (ImGui::GetStyle == ImGui) {
					//ImGui::StyleColorsLight();
				//}
				//else 
				// {
					//ImGui::StyleColorsDark();
				//}

			}

			// I couldn't figure this out yet.
			// This shows up for a second then dies.
			ImGui::Separator();
			if (!ImGui::Button("Click"))
			{
				DirectX9Test::button1_clicked = false;
			}
			else
			{
				DirectX9Test::button1_clicked = true;
			}

			if (!DirectX9Test::button1_clicked)
			{
				TextFunctions::SetBulletText("You clicked the button");
			}
			else
			{
				ImGui::BulletText("Button not pressed.");

				//ImGui::BulletText("You clicked the button!");
			}
			//}

								//if (ImGui::Button("Click"))
								//{

								//    setBulletText("You clicked the button");
								//    //ImGui::BulletText("You clicked the button!");
								//}
								//else 
								//{
								//    ImGui::BulletText("Button not pressed.");
								//}

			ImGui::Separator();


			// This below works for a dark mode toggle.
			// 5-16-2024 @ 9:14PM

#ifndef _TEST
#define _TEST
#endif


#ifdef _TEST
					// Well the checkbox is inverted lol, oh well I'll fix it later.
					// If it is checked it turns off dark mode, I guess its because I have dark mode as the default theme.
			if (!ImGui::Checkbox("Dark Mode", &DirectX9Test::dark_mode))
			{
				if (!DirectX9Test::dark_mode)
				{

					ImGui::StyleColorsDark();
					ImGui::BulletText("On");
				}
				else
				{
					ImGui::StyleColorsLight();
					ImGui::BulletText("Off");
				}
			}

#else
			ImGui::Checkbox("Dark Mode", &dark_mode);
			if (dark_mode)
			{
				ImGui::StyleColorsLight();
				ImGui::BulletText("Off");
			}
			else
			{
				ImGui::StyleColorsDark();

				ImGui::BulletText("On");
			}
#endif //_TEST
			// Disable preprocessor
#undef _TEST

					// This works for toggling the demo window on and off
			ImGui::Checkbox("Demo window", &DirectX9Test::show_demo_window);

			// Possibly implement feature to read from a text file and write it to some output box.
			//ImGui::Text("Test");

			//const char *test = "Test";

			//// I never did get this working yet.
			//// https://www.programiz.com/cpp-programming/buffer
			//char* buf = new char[40];
			////char InputBuf[256];
			//// https://stackoverflow.com/questions/502856/whats-the-difference-between-size-t-and-int-in-c
			//size_t num = 1;
			////char deref = &test;

			//// This doesn't work right.
			//if (ImGui::InputText("##Username", buf, num))
			//{
			//    //std::cout << buf;
			//}

			// This works.
			if (ImGui::IsMousePosValid())
				ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
			else
				ImGui::Text("Mouse pos: <INVALID>");

			//if (ImGui::Checkbox("Show Text", &toggle_text)) 
			//{
			//    ImGui::BulletText("Hello");
			//} 
			//else
			//{
			//    ImGui::BulletText("Hola");
			//}


			// How do I update this text in code?
			// Like if a button is pressed.
			//ImGui::Separator();
			//ImGui::BulletText("Test");

			// I'm quite sure this will only work on Windows, will need tested on Linux once I get opengl working.
#ifdef _WIN32

			static bool test = false;
			ImGui::Text("Key Press: ");
			ImGui::SameLine();
			//if (ImGui::Checkbox("Test", &test))
			ImGui::Checkbox("Test", &test);

			if (test)
			{
				// https://stackoverflow.com/questions/41600981/how-do-i-check-if-a-key-is-pressed-on-c
				/*Check if high-order bit is set (1 << 15)*/
				// I wonder if I can create a for loop to iterate over the list of keys


				// I couldn't get the below working.
				//char keyboard_chars[26] = { 'A', 'B', 'C', 'D',
				//'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
				//'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

				enum keyboard_chars_enum {
					A = 0, B, C, D,
					E, F, G, H, I, J, K, L, M, N, O,
					P, Q, R, S, T, U, V, W, X, Y, Z
				};

				//https://www.codeproject.com/Questions/207914/To-get-Number-of-elements-in-typedef-struct
				char input = Z - A;

				////int test = 1;

				// https://cplusplus.com/forum/beginner/6463/
				// I never did get this working
				//switch (keyboard_chars_enum)
				//switch (input)
				//{
				//case A:
				//	ImGui::Text("A Key pressed");
				//}

				//for (int i =0; i< keyboard_chars_enum)
				// This one didn't work
				//for (int i = 0; i < input; i++) {
				//	if (GetKeyState(i) & 0x8000)
				//		ImGui::Text(i + " key was pressed");
				//}


				// This works
				//if (GetKeyState('A') & 0x8000)
				//{
				//	ImGui::Text("A Key pressed");
				//}

				//if (GetKeyState(VK_SHIFT) & 0x8000)
				//{
				//	ImGui::Text("Shift Key pressed");
				//}
				//
			}
			else
			{
				ImGui::Text("Goodbye");
			}
#endif //_WIN32


			//#define _TEST
			//#ifdef _TEST
			//			ImGui::Checkbox("Define Test", &DirectX9Test::define_test);
			//
			//			if (define_test)
			//			{
			//				ImGui::Text("Value of limit is: " + LIMIT);
			//				//std::cout << "Value of limit is " << LIMIT;
			//			}
			//#endif //_TEST
			//#undef _TEST



			ImGui::Checkbox("List values", &DirectX9Test::list_values);

			if (DirectX9Test::list_values)
			{
				ImGui::Text(KeyStates::charTest());


				//Sleep(2000);
				// This spams the console too much.
				KeyStates::test();
			}
			else
			{
				ImGui::Text("Disabled");
			}
		}

		// This works for a column, having multiple items on the same row.
		ImGui::Columns(2);
		ImGui::Text("Hello");
		ImGui::NextColumn();
		ImGui::Text("World");

		ImGui::Columns(1);
	//}
}