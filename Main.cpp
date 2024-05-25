#ifdef _TEST
#ifdef _DIRECTX9
// Dear ImGui: standalone example application for DirectX 9

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp


#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#endif

#include <d3d9.h>
#include <tchar.h>

#include <string>
#include <iostream>
#include <fstream>

#include "util/textFileFunctions.h"

// https://www.geeksforgeeks.org/macros-and-its-types-in-c-cpp/
// Test macros
#define LIMIT 5

// Test code
#ifndef _TEST
#define _TEST
#endif

// Data
static LPDIRECT3D9              g_pD3D = nullptr;
static LPDIRECT3DDEVICE9        g_pd3dDevice = nullptr;
static UINT                     g_ResizeWidth = 0, g_ResizeHeight = 0;
static D3DPRESENT_PARAMETERS    g_d3dpp = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void ResetDevice();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

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

static void setBulletText(const char* text)
{
    ImGui::BulletText(text);
}

//

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
    std::string num1_string = std::to_string(num1);
    std::string num2_string = std::to_string(num2);
    std::string sum_string = std::to_string(sum);

    return "The value of " + num1_string + " + " + num2_string + " = " + sum_string;
}


// imgui_demo line 256
static void ShowWindow(bool* p_open)
{
    static bool show_main_menu = false;

    if (show_main_menu)
    {
        if (ImGui::Begin("Test"))
        {
            ImGui::Text("Hello World!");
        }
    }

    if (!ImGui::Begin("Test", p_open))
    {
    
        ImGui::End();
        return;
    }


}

// Main code
int main(int, char**)
{

#ifdef _TEST
    //std::cout << testString1();
    std::cout << "Hello world!";

#else
    // Create application window
//ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX9 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, wc.hInstance, nullptr);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX9_Init(g_pd3dDevice);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Show window
    // Main loop
    bool done = false;
    bool button1_clicked = false;
    static bool show_app_main_menu_bar = false;
    //static bool toggle_text = false;
    static bool dark_mode = false;
    static bool define_test = false;

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
        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            g_d3dpp.BackBufferWidth = g_ResizeWidth;
            g_d3dpp.BackBufferHeight = g_ResizeHeight;
            g_ResizeWidth = g_ResizeHeight = 0;
            ResetDevice();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        if (ImGui::Begin("My new window", nullptr, ImGuiWindowFlags_MenuBar))
        {
            // Menu bar
            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("Test"))
                {
                    ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
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
                    button1_clicked = false;
                }
                else
                {
                    button1_clicked = true;
                }

                if (!button1_clicked)
                {
                    setBulletText("You clicked the button");
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
                if (!ImGui::Checkbox("Dark Mode", &dark_mode))
                {
                    if (!dark_mode)
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
                ImGui::Checkbox("Demo window", &show_demo_window);


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


#ifdef _TEST
                ImGui::Checkbox("Define Test", &define_test);

                if (define_test)
                {
                    ImGui::Text("Value of limit is: " + LIMIT);
                    std::cout << "Value of limit is " << LIMIT;
                }
#endif //_TEST

            }

            // End main test menu



            // Text file functions test menu
            if (ImGui::CollapsingHeader("Text File Functions"))
            {
                ImGui::BulletText("I will add reading files, writing and more to this.");
                ImGui::Separator();

                // I almost got this working 5-17-2024 @ 3:14PM
                // It doesn't print out all of the lines from the return value.
                if (ImGui::Button("Test"))
                {
                    TextFileFunctions::printTextOutput("test.txt");
                    //std::cout << TextFileFunctions::printTextOutput("test.txt") << std::endl;
                }
            }
            // End Text file functions test menu

            //if (ImGui::BeginMenu("My menu"))
            //{
            //    //ImGui::BulletText("You should see this");
            //    ImGui::MenuItem("test", NULL);
            //    ImGui::EndMenu();
            //}



        }
        // End ImGui
        ImGui::End();

        // Rendering
        ImGui::EndFrame();
        g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        g_pd3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        D3DCOLOR clear_col_dx = D3DCOLOR_RGBA((int)(clear_color.x * clear_color.w * 255.0f), (int)(clear_color.y * clear_color.w * 255.0f), (int)(clear_color.z * clear_color.w * 255.0f), (int)(clear_color.w * 255.0f));
        g_pd3dDevice->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clear_col_dx, 1.0f, 0);
        if (g_pd3dDevice->BeginScene() >= 0)
        {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            g_pd3dDevice->EndScene();
        }
        HRESULT result = g_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr);

        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
#endif //_TEST


}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    if ((g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == nullptr)
        return false;

    // Create the D3DDevice
    ZeroMemory(&g_d3dpp, sizeof(g_d3dpp));
    g_d3dpp.Windowed = TRUE;
    g_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    g_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    g_d3dpp.EnableAutoDepthStencil = TRUE;
    g_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_d3dpp, &g_pd3dDevice) < 0)
        return false;

    return true;
}

void CleanupDeviceD3D()
{
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
    if (g_pD3D) { g_pD3D->Release(); g_pD3D = nullptr; }
}

void ResetDevice()
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);
    ImGui_ImplDX9_CreateDeviceObjects();
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
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

#else

#include <string>
#include <iostream>



// Main code
// I moved the DirectX9 code into the test/directx9_test.cpp file,
// The code above is disabled with a preprocessor.

#ifdef _DIRECTX9
#include "test/directx9_test.h"
#endif //_DIRECTX9

#ifdef _OPENGL
#include "test/opengl_test.h"
#endif //_OPENGL

int main(int, char**)
{
#ifdef _DIRECTX9
    DirectX9Test::directX9Test();
#endif //_DIRECTX9

#ifdef _OPENGL
    OpenGLTest::openGLTest();
#endif //_OPENGL
    
    //std::cout << "Hello World";
}
#endif // _TEST