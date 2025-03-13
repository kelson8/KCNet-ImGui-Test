#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif //_WIN32

// Oops I named the source file with a .c extension instead of .cpp
// No wonder this didn't work.
// https://stackoverflow.com/questions/12524168/resolving-found-at-file-scope-missing-function-header-in-vs2010-c

#ifdef _TEST2
class Helpers {
public:
#ifdef _WIN32
	static bool CreateDeviceD3D(HWND hWnd);
	static void CleanupDeviceD3D();
	static void ResetDevice();

#ifdef _TEST2
	static LPDIRECT3D9              g_pD3D;
	static LPDIRECT3DDEVICE9        g_pd3dDevice;
	static UINT                     g_ResizeWidth;
	static UINT						g_ResizeHeight;
	static D3DPRESENT_PARAMETERS    g_d3dpp;

#endif //_TEST2

#else
	// Will this work on Linux or Mac? I don't think DirectX does.
	static bool CreateDeviceD3D();
#endif 
};
#endif //_TEST2


