#pragma once
#include <iostream>


// https://www.w3schools.com/cpp/cpp_constructors.asp

class Car
{
public:
	std::string brand;
	std::string model;
	int year;
	Car(std::string x, std::string y, int z); // Constructor declaration
};

