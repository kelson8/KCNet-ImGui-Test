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
	}
}

//class ImGuiFunctions
//{
//};

