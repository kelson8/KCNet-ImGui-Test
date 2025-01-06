#include "constructor_test.h"


// TODO Attempt to call in the main class or where ever the hell I'm doing this ImGui test.
Car::Car(std::string x, std::string y, int z) {
	brand = x;
	model = y;
	year = z;
}