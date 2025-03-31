#include "pch.h"

#include "imgui.h"
#ifdef _WIN32
#include <Windows.h>
#include "directx9_test.h"

#include "keystates.h"
#endif

#include "text_functions.h"

#include "test_menu2.h"

void TestMenu2::TestMenu()
{
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
	}
	//

	// Disabled, these are just for testing.
	// This works for a column, having multiple items on the same row.
	//ImGui::Columns(2);
	//ImGui::Text("Hello");
	//ImGui::NextColumn();
	//ImGui::Text("World");

	//ImGui::Columns(1);
//}

}