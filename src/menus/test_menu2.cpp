#include "pch.h"

#include "imgui.h"
#ifdef _WIN32
#include <Windows.h>
#include "directx9_test.h"

#include "keystates.h"
#endif

#include "text_functions.h"

#include "test_menu2.h"

#include "imgui_defines.h"
// New for random numbers and other util
#include "misc_util.h"

// Functions for clamping the inputs for values and other stuff
#include "imgui_functions.h"

// I don't think the exe names should really be too long
// https://www.thoughtco.com/definition-of-buffer-p2-958030
//char* buf = new char[30];
char memoryBaseBuffer[30] = ""; // Allocate on the stack. Choose a suitable size.

void TestMenu2::TestMenu()
{
	// Init the random number to 0 by default
	static int randomNumber = 0;
	
	// Set defualt min and max values
	static int testMin = 0;
	static int min = 0;
	static int max = 1000;

	MiscUtil miscUtil = MiscUtil();

	const int vsprintBufferSize = 1024;
	char* vsPrintBuffer = new char[vsprintBufferSize];
	if (ImGui::CollapsingHeader("test2"))
	{
		// Disabled, doesn't work.
#ifdef _TEST1
		if (ImGui::Button("Test"))
		{
			char format[] = "Hello %s";
			std::cout << "Hello" << std::endl;

			call_vsprintf_s(vsPrintBuffer, 15, format);
		}
#endif //_TEST1

		//ImGui::SliderInt("Min/Max", &testMin, min, max);


		// From ReVC
		//ImGui::Text("Minimum number: 23, Maximum number: 59");
		// TODO Come up with a better solution for this.
		//ImGuiFunctions::Input::InputIntMax("Minimum", &min, 1, 10, 23);

		//ImGuiFunctions::Input::InputIntClamp("Maximum", &max, 1, 10, 0, 59);

		IMGUITEXT("Random Number Generator");

		IMGUI_INPUT_INT("Minimum", &min);
		IMGUI_INPUT_INT("Maximum", &max);



		// This works outputting to a message box, I switched to using ImGui text.
		if (IMGUIBUTTON("Generate random number"))
		{
			// Some random value
			//int value = miscUtil.GenerateRandomNumber(1, 1000);
			//randomNumber = miscUtil.GenerateRandomNumber(1, 1000);
			randomNumber = miscUtil.GenerateRandomNumber(min, max);
//#ifdef _WIN32
//			// Convert the integer to a string
//			std::stringstream ss;
//			//ss << "Random number: " << value;
//			ss << "Random number: " << randomNumber;
//			std::string strValue = ss.str();
//			std::wstring wStrValue(strValue.begin(), strValue.end());
//
//			// Switch to using MessageBoxW
//			MessageBoxW(NULL, wStrValue.c_str(),
//			L"KCNet-ImGuiTest", MB_OK);
//
//
//			//MessageBox(NULL, TEXT("Hello From ImGui, a MessageBox"),
//			//MessageBox(NULL, TEXT("Random number: " + value),
//			//	TEXT("KCNet-ImGuiTest"), MB_OK);
//#endif
		}

		std::string randomNumberText = "Random number: " + MiscUtil::toString(randomNumber);
		IMGUITEXT(randomNumberText.c_str());

		// End random number generator

		IMGUI_SEPERATOR();
		IMGUITEXT("Folder utils");
		ImGuiFunctions::Folders::OpenCurrentDirectoryButton("Open current directory");

		IMGUI_SEPERATOR();
		
		IMGUITEXT("Memory address testing");
		

		// Well this makes the random number glitch out.. Oops.
		//ImGui::InputText("Exe Name", buf, 20);
		ImGui::InputText("Exe Name", memoryBaseBuffer, sizeof(memoryBaseBuffer));
		if (IMGUIBUTTON("Display base address")) 
		{
			// Make sure there is a value in the buffer
			// TODO Add error handling to check for invalid or not found exe.
			//if (buf)
			if (memoryBaseBuffer)
			{
				if (memoryBaseBuffer[0] != '\0') {
					miscUtil.LogBaseAddress(memoryBaseBuffer);
				}
				// TODO Fix this
				//else {
				//	ImGui::Text("Please enter an exe name.");
				//}
			}
		}	
		IMGUI_SEPERATOR();



		// End directory testing

		//if (IMGUIBUTTON("Open Current Directory"))
		//{
		//	
		//}
		

	}
	// End test2 header

	// Disabled, these are just for testing.
	// This works for a column, having multiple items on the same row.
	//ImGui::Columns(2);
	//ImGui::Text("Hello");
	//ImGui::NextColumn();
	//ImGui::Text("World");

	//ImGui::Columns(1);
//}

}