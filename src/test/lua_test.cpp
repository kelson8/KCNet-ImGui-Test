#include "lua_test.h"

#include <string>
#include <iostream>

/// <summary>
/// Set the lua state, and load the lua libraries
/// </summary>
LuaTest::LuaTest() {
	m_luaVM = luaL_newstate();

	// Load LUA libraries, TODO is this needed in here?
	luaopen_base(m_luaVM);
	luaopen_math(m_luaVM);
	luaopen_string(m_luaVM);
	luaopen_table(m_luaVM);
	luaopen_debug(m_luaVM);
	luaopen_utf8(m_luaVM);
	luaopen_os(m_luaVM);

}

/// <summary>
/// Check lua globals, made this into a function
/// </summary>
/// <param name="L"></param>
/// <param name="r"></param>
/// <returns></returns>
bool
LuaTest::CheckLua(lua_State* L, int r)
{
	// Check if the value is valid
	if (r != LUA_OK) {
		std::string errorMsg = lua_tostring(L, -1);
		 std::cout << errorMsg << std::endl;
		return false;
	} /*else {
			std::cout << errorMsg << std::endl;
	}*/

	return true;
}

// All functions used in lua scripts need to be in 'extern "C" {}' blocks
// When defining a lua function in here, make it like this:
/*
	int FunctionNameLua(lua_State* L)
	
	// The return can be how many variables you want this to use.
	// For the LogMessageToConsoleLua function, it has a return value of 1 because it
	// only takes the string from the lua file like this:
	// print_msg("This will display in cout")
	
	return 1;

	// If this has multiple variables needed, such as for coordinates in a game
	// You can change this to 3 for an X, Y, Z
	// set_coordinates(x, y, z);
	return 3;

	
* 
*/
extern "C"
{
	/// <summary>
	/// Log a message to cout using lua
	/// </summary>
	/// <param name="L"></param>
	/// <returns></returns>
	int LogMessageToConsoleLua(lua_State* L)
	{
		std::string messageToLog = (std::string)lua_tostring(L, 1);
		std::cout << messageToLog << std::endl;

		return 1;
	}

}

/// <summary>
/// I had to add this to the class to fix it.
/// I got this working, I had to add lua_State *L and get the lua state
/// To move this back into the init function if needed:
/// Rename the 'L' variable in each lua_register to 'm_luaVM'
/// </summary>
void
LuaTest::RegisterLuaFunctions(lua_State* L)
{
	// Register functions like this
	lua_register(L, "print_msg", LogMessageToConsoleLua);
}

/// <summary>
/// TODO Setup events to run, I may need to add a delay to some of this.
/// This would go in the main loop if I decide to use events in this ImGui test.
/// </summary>
#ifdef LUA_EVENT_TEST
void
LuaTest::LuaEvents()
{
	Defines defines = Defines();
	LuaTest luaTest = LuaTest();

	luaTest.RegisterLuaFunctions(m_luaVM);

	if (CheckLua(m_luaVM, luaL_dofile(m_luaVM, defines.luaEventsScript.c_str())))
	{
	}
	else {
		std::cout << "The lua file " << defines.luaEventsScript << "Couldn't be loaded!" << std::endl;
	}

}
#endif


/// <summary>
/// This runs the init lua function, but it can be run multiple times
/// </summary>
void
LuaTest::InitLua()
{
	Defines defines = Defines();
	LuaTest luaTest = LuaTest();


	//lua_State *L = LuaTest::GetInstance().GetLuaState();

	luaTest.RegisterLuaFunctions(m_luaVM);

	// This seems to work for error handling if the file doesn't exist
	if (CheckLua(m_luaVM, luaL_dofile(m_luaVM, defines.luaScript.c_str()))) 
	{
		//std::cout << defines.luaScript << " exists!" << std::endl;
	}
	else {
		std::cout << defines.luaScript << " doesn't exist!" << std::endl;
	}


}

