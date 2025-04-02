#pragma once

#if _WIN32
#include <Windows.h>
#endif

#include <string.h>
#include <iostream>

// Enable lua test
#define LUA_TEST

// Enable the lua event test, this is disabled until I'm ready to use it.
//#define LUA_EVENT_TEST

//

// TODO Fix this to work in the OpenGL test
#ifdef _WIN32
class Defines {
private:
	// Defining all of these in a private class, they will be called under the public class.
	// Kind of mimics my Java Messages file from KBP: https://github.com/kelson8/KBP/blob/master/src/main/java/net/Kelsoncraft/KBP/util/Messages.java
	// https://stackoverflow.com/questions/50332569/why-i-am-getting-this-error-constexpr-is-not-valid-here
	static constexpr wchar_t* TITLE = L"KCNet ImGui DirectX Test";

	// TODO Add more of these
	static constexpr wchar_t* MAIN_MENU_TITLE_ = L"Main Menu";
	static constexpr char* IMGUI_WINDOW_NAME_ = "KCNet ImGui";

public:
	const wchar_t* window_title = TITLE;
	const wchar_t* main_menu_title = MAIN_MENU_TITLE_;
	const char* imgui_window_name = IMGUI_WINDOW_NAME_;

	// Lua script files
	static std::string luaScript;
	static std::string luaEventsScript;
};




#endif //_WIN32