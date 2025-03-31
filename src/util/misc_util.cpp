#include "misc_util.h"

#include <iostream>
#include <random>
#include <string>

#define NEW_RANDOM_NUMBER_GEN

/// <summary>
/// Convert a float to a string, instead of using std::to_string everywhere.
/// </summary>
/// <param name="value">The float to convert</param>
/// <returns>The float converted to string</returns>
std::string
MiscUtil::floatToString(float value)
{
	std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string
MiscUtil::AddressToString(void* address)
{
	std::stringstream ss;
	ss << address;
	return ss.str();
}

/// <summary>
/// Generate a random number, this takes a minimum and maximum value
/// https://stackoverflow.com/questions/29381843/generate-random-number-in-range-min-max
/// </summary>
/// <param name="min">The minimum number to generate.</param>
/// <param name="max">The maximum number to generate.</param>
/// <returns>A random number between min and max.</returns>
int
MiscUtil::GenerateRandomNumber(int min, int max)
{

#ifdef NEW_RANDOM_NUMBER_GEN
	// Use std::random_device to seed the generator
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
#else
	srand(time(0));
	// Get a random number between min and max
	int randomNum = min + rand() % (max - min + 1);
	return randomNum;
#endif
}

