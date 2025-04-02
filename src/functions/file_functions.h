#pragma once

#include <string>

class FileFunctions {
public:
#ifdef _WIN32
	// TODO Fix for Linux

	// Folder stuff
	static bool DoesFileExist(const std::string& fileName);
	static std::string CurrentDirectory();

#endif
};