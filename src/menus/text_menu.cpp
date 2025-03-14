#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "./util/keystates.h"
#endif

#include <d3d9.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

// Utility functions
#include "text_file_functions.h"

// Test functions
#include "directx9_test.h"

// Menus
#include "./menus/text_menu.h"

bool show_text = false;

void TextMenu::TextMainMenu() {
	ImGui::BulletText("I will add reading files, writing and more to this.");
	ImGui::Separator();

	// I almost got this working 5-17-2024 @ 3:14PM
	// It doesn't print out all of the lines from the return value.
	
	ImGui::Checkbox("Test", &show_text);

	if(show_text)
	{
		// This just spams the console.
		//TextFileFunctions::printTextOutput("test.txt");
		
		// This works!!!
		// Why? I didn't think this would print multiple lines.
		//outputTextFileContents("test.txt");
		TextFileFunctions::outputTextFileContents("test.txt");
	}


	//if (ImGui::Button("Test"))
	//{
	//	TextFileFunctions::printTextOutput("test.txt");
	//	//std::cout << TextFileFunctions::printTextOutput("test.txt") << std::endl;
	//}
}