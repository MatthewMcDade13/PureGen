#include "stdafx.h"
#include "Generator.h"

#include <iostream>

Generator::Generator(std::string className, std::string parentClass)
	: className(className), parentClass(parentClass)
{ }

Generator::~Generator()
{
}

void Generator::GenerateTemplate()
{
	std::cout << "Clas Name: " << className << std::endl;
	std::cout << "Parent Class: " << parentClass << std::endl;
}