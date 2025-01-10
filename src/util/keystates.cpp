#include "keystates.h"
#include <string>
#include <iostream>

// What was this file doing?
char keyboard_chars[26] = { 'A', 'B', 'C', 'D',
					'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 
					'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static void chars()
{
	std::cout << keyboard_chars;
}

char* KeyStates::charTest()
{
	return keyboard_chars;
}

// I wonder how to return the list of arrays?
void KeyStates::test()
{
	for (int i = 0; i < keyboard_chars[i]; i++)
	{
		std::cout << keyboard_chars[i] << " [" << i << "]" <<std::endl;
	}
}



//static char cars()
//{
//	return &cars;
//}