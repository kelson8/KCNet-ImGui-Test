#pragma once

#ifdef _WIN32
#include <Windows.h>
#endif

namespace ImGuiFunctions {
	namespace Main {
		static void HelpMarker(const char* desc);
		// TODO What's this for? Seems like it's not needed
		//static void ShowWindow(bool* p_open);
		void SetupContext();
		void ShowWindow(HWND hwnd);
		void ShutDown();
		void DestroyWindow(HWND hwnd, WNDCLASSEXW wc);
		void ApplyStyle();



	}

	namespace Input {
		// For setting a min/max value on ImGui::InputInt
// Set it to just have a maximum value
		void InputIntMax(const char* label, int* v, int step = 1, int step_fast = 10, int max_value = 100);
		// Set it to have a minimum and maximum value
		void InputIntClamp(const char* label, int* v, int step = 1, int step_fast = 10, int min_value = 0, int max_value = 100);
	}

	namespace Folders {
		std::string GetCurrentWorkingDirectory();
		void OpenCurrentDirectoryButton(const char* buttonLabel);
		void OpenDirectoryButton(std::string folder, const char* buttonLabel);
	}
}

//class ImGuiFunctions
//{
//};

