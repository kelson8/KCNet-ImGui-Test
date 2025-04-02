#include "file_functions.h"

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#endif

//------------- File functions ---------------/

#ifdef _WIN32
bool FileFunctions::DoesFileExist(const std::string& fileName)
{
	std::ifstream file(fileName);
	return file.good();
}

std::string FileFunctions::CurrentDirectory()
{
    char current_dir[MAX_PATH];
    if (GetCurrentDirectoryA(MAX_PATH, current_dir) != 0)
    {
        return current_dir;
    }
    else {
        return "Error getting current directory.";
    }
}

#endif

//------------- End file functions ---------------/
