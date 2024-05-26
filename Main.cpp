
// Test main method can go in here, can be useful for quick testing in the console.
//#define _TEST
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