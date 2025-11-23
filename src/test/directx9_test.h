#pragma once
#ifdef _WIN32
#include <Windows.h>


#ifdef _DIRECTX9
#include <d3d9.h>

class DirectX9Test {
public:
	static void directX9Test();
	static bool show_app_main_menu_bar;
	static bool button1_clicked;
	static bool dark_mode;
	static bool define_values;
	static bool list_values;
	static bool show_demo_window;
	static bool define_test;
	static bool toggle_text;

	static bool display_cpp_version;

	// Data

// TODO Make these public, add them into the header.
// That should fix this to work in the helpers.cpp
	static LPDIRECT3D9              g_pD3D;
	// Oh, having these undefined in the directx9_test.cpp 
	// causes unresolved external symbol errors.
	static LPDIRECT3DDEVICE9        g_pd3dDevice;
	static UINT                     g_ResizeWidth, g_ResizeHeight;
	static D3DPRESENT_PARAMETERS    g_d3dpp;
};

#endif // _DIRECTX9
#endif //_WIN32