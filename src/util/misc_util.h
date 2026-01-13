#pragma once
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

// Some of these came from my ReVC project

class MiscUtil
{
public:
	// Return the current C++ version
	std::string CPlusPlusVersion();

	// Convert a memory address to a string
	// Takes a value like '&pPlayer->m_fHealth' or any variable.
	std::string AddressToString(void* address);

	// Random number generator with a min and max value.
	static int GenerateRandomNumber(int min, int max);


	// Template to convert float, int, and other values that can be converted to a string.
	template <typename T>
	static std::string toString(T value) {
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	// Convert a float to a string
	std::string floatToString(float value);

#ifdef _DIRECTX9
	// Memory address testing
	// Display the base address of a program in the console
	// Logs the return value of the below function, GetModuleBaseAddress.
	void LogBaseAddress(const char* exeName);

	// Get the base address of a program, this doesn't log it.

	uintptr_t GetModuleBaseAddress(const char* exeName);
	//uintptr_t GetModuleBaseAddress(const wchar_t* exeName);
#endif // _DIRECTX9
};

