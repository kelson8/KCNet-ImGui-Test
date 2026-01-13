#pragma once


#include "defines.h"
#ifdef LUA_TEST
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
#endif


class LuaTest
{
private:

#ifdef LUA_TEST
	// Set the lua state
	lua_State* m_luaVM;

	// Register the lua functions
	void RegisterLuaFunctions(lua_State* L);
#endif // LUA_TEST
public:

#ifdef LUA_TEST
	LuaTest();
	void InitLua();

	bool CheckLua(lua_State* L, int r);

	// Run the custom event system I am working on in Lua
#ifdef LUA_EVENT_TEST
	void LuaEvents();
#endif

	// These work for getting the m_luaVM variable in the private class above.
	
	// Return the instance of LuaTest
	static LuaTest& GetInstance()
	{
		static LuaTest instance;
		return instance;
	}

	// Get the lua state, can be used like this:
	// lua_State *L = LuaTest::GetInstance().GetLuaState();
	lua_State* GetLuaState()
	{
		return m_luaVM;
	}

	// Close the lua vm
	~LuaTest()
	{
		if (m_luaVM)
		{
			lua_close(m_luaVM);
		}
	}

#endif // LUA_TEST
};

