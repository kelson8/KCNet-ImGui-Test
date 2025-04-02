#include "defines.h"
#include "misc_util.h"
#include "file_functions.h"

std::string currentDirectory = FileFunctions::CurrentDirectory();
std::string luaScriptsDirectory = currentDirectory + "\\lua_scripts\\";

std::string Defines::luaScript = luaScriptsDirectory + "test.lua";
std::string Defines::luaEventsScript = luaScriptsDirectory + "kcnet-events.lua";