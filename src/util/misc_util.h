#pragma once
#include <iostream>
#include <sstream>
#include <string>

// Some of these came from my ReVC project

class MiscUtil
{
public:
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


};

