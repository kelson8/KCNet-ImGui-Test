#include "pch.h"

#include "defines.h"
#include "lua_menu.h"
#include "test_menu1.h"

#include "imgui.h"
#ifdef _WIN32
#include <Windows.h>
#include "directx9_test.h"

#include "keystates.h"
#endif

#include "text_functions.h"

#include "imgui_functions.h"

#include "misc_util.h"

#ifdef LUA_TEST
#include "lua_test.h"
#endif

#ifdef LUA_TEST
void LuaMenu::LuaMainMenu() {
	ImGui::Text("I will lua testing into this menu later.");
	
	ImGui::Separator();

	// TODO Come up with a better solution for this later.
	if (ImGui::Button("Run lua file"))
	{
		LuaTest luaTest = LuaTest();
		luaTest.InitLua();
	}
	

	//ImGui::Checkbox("Test", &show_text);
}

#endif //LUA_TEST