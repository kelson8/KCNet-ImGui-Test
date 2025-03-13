#include "helpers.h"

#include "imgui.h"
#ifdef _DIRECTX9
#include <d3d9.h>


#include "imgui_impl_dx9.h"

#include "directx9_test.h"



//-------------- DirectX9 Functions --------------/

void Helpers::InitializeD3D(HWND hwnd, WNDCLASSEXW wc)
{
	// Initialize Direct3D
	if (!Helpers::CreateDeviceD3D(hwnd))
	{
		Helpers::CleanupDeviceD3D();
		::UnregisterClassW(wc.lpszClassName, wc.hInstance);
	}
}

bool Helpers::CreateDeviceD3D(HWND hWnd)
{
	if ((DirectX9Test::g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
		return false;

	// Create the D3DDevice
	ZeroMemory(&DirectX9Test::g_d3dpp, sizeof(DirectX9Test::g_d3dpp));
	DirectX9Test::g_d3dpp.Windowed = TRUE;
	DirectX9Test::g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	DirectX9Test::g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
	DirectX9Test::g_d3dpp.EnableAutoDepthStencil = TRUE;
	DirectX9Test::g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	DirectX9Test::g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;



	//DirectX9Test::g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
	if (DirectX9Test::g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DirectX9Test::g_d3dpp, &DirectX9Test::g_pd3dDevice) < 0)
		return false;

	return true;
}

void Helpers::CleanupDeviceD3D()
{
	if (DirectX9Test::g_pd3dDevice)
	{
		DirectX9Test::g_pd3dDevice->Release();
		DirectX9Test::g_pd3dDevice = nullptr;
	}
	if (DirectX9Test::g_pD3D)
	{
		DirectX9Test::g_pD3D->Release();
		DirectX9Test::g_pD3D = nullptr;
	}
}

void Helpers::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = DirectX9Test::g_pd3dDevice->Reset(&DirectX9Test::g_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

#endif //_DIRECTX9