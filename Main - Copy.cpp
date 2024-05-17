#include <iostream>
#include <string>
#include <print>

// Fixes it to where I don't need to use std::cout and std::string
using namespace std;

int main()
{
	// This is a way to define multiple variables at once
	int player1_score = 25, player2_score = 40;

	// Variable declaration
	int player3_score;
	// Variable initialisation
	player3_score = 22;

	// Constants (These can't be changed later)
	const string playername = "kelson8";
	
	// Pointer test (Both of these are valid)
	const int *ptr = &player2_score;
	const string* ptr1 = &playername;

	// "endl" makes a new line
	// either "cout" or "printf" can be used to output text.
	//cout << "Hello " << playername << " welcome to the party!" << endl;
	//cout << "Nice, you got a high score of " << player2_score << endl;
	
	// This needs the * on it or it don't work right since it's a pointer, I still don't fully understand how these work.
	cout << *ptr1 << " " << *ptr;

	// Newest C++ preview required for this to work.
	//std::print("Hello {}, welcome to the party!", playername);
	//std::print("Test");

	// Why doesn't this printf work right?
	//printf("Hello %s welcome to the party", playername);
	//printf("Nice, you got a high score of %s", player2_score);

	return 0;
}