
// Test main method can go in here, can be useful for quick testing in the console.
//#define _TEST
// TODO Fix this to work... It just dies?
// TODO Actually fix Linux support with CMake, make this build on Windows and Linux with CMake.
#ifdef _TEST
#include <string.h>
#include <iostream>

int main(int, char**)
{
    
    std::cout << "Hello World!" << std::endl;
    return 0;
}

#else

#include <string>
#include <iostream>
#include <windows.h>

// Main code
// I moved the DirectX9 code into the test/directx9_test.cpp file,

#ifdef _DIRECTX9
#include "./test/directx9_test.h"
#endif //_DIRECTX9

#ifdef _OPENGL
#include "test/opengl_test.h"
#endif //_OPENGL

// New
#include <shellapi.h>


// https://stackoverflow.com/questions/14954876/how-to-create-a-message-box-with-user-defined-buttons-in-c
/*
 * MessageBox() Flags
 * These could be useful.
 */

//#define MB_OK                       0x00000000L
//#define MB_OKCANCEL                 0x00000001L
//#define MB_ABORTRETRYIGNORE         0x00000002L
//#define MB_YESNOCANCEL              0x00000003L
//#define MB_YESNO                    0x00000004L
//#define MB_RETRYCANCEL              0x00000005L
//#if(WINVER >= 0x0500)
//#define MB_CANCELTRYCONTINUE        0x00000006L
//#endif /* WINVER >= 0x0500 */

// Needed for the dll, what exactly does this do?
typedef VOID(*DLLPROC) (LPTSTR);

int main(int, char**)
{
#define _TEST1
    // Load a test dll
    // Get path to the dll, use current path
    // https://stackoverflow.com/questions/61382829/dynamically-use-a-dll-from-a-console-application

    // https://www.tutorialspoint.com/dll/dll_writing.htm
    // This seems to inject but I don't see the message box pop up

#ifdef _TEST1
#ifdef _DIRECTX9

    // I forgot about making a test DLL for this project.
    // DLL initialize

#ifdef DLL_TEST
    HINSTANCE hinstDLL;
    DLLPROC HelloWorld;
    BOOL fFreeDLL;
    hinstDLL = LoadLibrary("KCNet-TestDll.dll");
    const std::string url = "https://git.internal.kelsoncraft.net/";

    if (!hinstDLL) 
    {
        // Well this seems to work well for an error message.
        // TODO Add clickable links in this.
        //Link is here: https://git.internal.kelsoncraft.net/"
        //MessageBox(NULL, TEXT("You need the KCNet-TestDll.dll for this to work.\n Would you like to visit the link?: "),           
        //    TEXT("Dll not found!"), MB_YESNO);

        // https://stackoverflow.com/questions/12578642/how-to-detect-which-yes-no-cancel-button-was-clicked-in-a-messagebox
        const int result = MessageBox(NULL, TEXT("You need the KCNet-TestDll.dll for this to work.\n Would you like to visit the link?: "),           
            TEXT("Dll not found!"), MB_YESNO);

        switch (result) 
        {
        case IDYES:
            // https://stackoverflow.com/questions/17347950/how-do-i-open-a-url-from-c
            //ShellExecute(0, 0, TEXT(url), 0, 0, SW_SHOW);
            // I was able to remove the char* from the above by using c_str() on url.
            ShellExecute(0, 0, url.c_str(), 0, 0, SW_SHOW);
            break;
        case IDNO:
            break;
        }

        std::cout << "Could not find the dynamic library." << std::endl;
        return EXIT_FAILURE;

    // Continue with program if dll is found
    }
    else 
    {
        std::cout << "Dynamic library loaded." << std::endl;
        HelloWorld = (DLLPROC)GetProcAddress(hinstDLL, "HelloWorld");

        // Run the message box prompt if it exists.
        if (HelloWorld != NULL)
            (HelloWorld);

        // Unload the dll
        fFreeDLL = FreeLibrary(hinstDLL);
    }

    // End DLL initialize


#endif //DLL_TEST

#endif //_DIRECTX9
#endif //_TEST1



    

#ifdef _DIRECTX9
    DirectX9Test::directX9Test();
#endif //_DIRECTX9

#ifdef _OPENGL
    OpenGLTest::openGLTest();
#endif //_OPENGL

// TODO Add these sometime
#ifdef _DIRECTX11

#endif //_DIRECTX11

#ifdef _DIRECTX12
#endif //_DIRECTX11
    
    //std::cout << "Hello World";
}
#endif // _TEST