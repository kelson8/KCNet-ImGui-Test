#include "imgui.h"
#include "imgui_impl_dx9.h"

#if _WIN32
#include "imgui_impl_win32.h"
#include <Windows.h>
#include "../util/keystates.h"
#endif

// My code
#include "text_functions.h"

void TextFunctions::SetBulletText(const char* text)
{
	ImGui::BulletText(text);
}