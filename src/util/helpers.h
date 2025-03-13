#pragma once
#ifdef _WIN32
#include <Windows.h>

#ifdef _DIRECTX9
#include <d3d9.h>
#endif

#include "defines.h"

#endif //_WIN32

// Oops I named the source file with a .c extension instead of .cpp
// No wonder this didn't work.
// https://stackoverflow.com/questions/12524168/resolving-found-at-file-scope-missing-function-header-in-vs2010-c

#ifdef _DIRECTX9
class Helpers {
public:
	// Never really used this preprocessor format before, but these should only be used in DirectX9 and on Windows.
	// https://stackoverflow.com/questions/17237545/preprocessor-check-if-multiple-defines-are-not-defined
#if defined(_WIN32) && defined(_DIRECTX9)
	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void ResetDevice();

	static void InitializeD3D(HWND hwnd, WNDCLASSEXW wc);
#else
	// Will this work on Linux or Mac? I don't think DirectX does.
	//static bool CreateDeviceD3D();
#endif 
};

#endif //_DIRECTX9

