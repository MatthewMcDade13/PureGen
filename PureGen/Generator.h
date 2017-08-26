#pragma once

#include <string>

class Generator
{
private:
	std::string className;
	std::string parentClass;


public:
	Generator(std::string className, std::string parentClass = "");	
	~Generator();

	void GenerateTemplate();

private:
	Generator(const Generator& other) = delete;
	Generator& operator=(const Generator& rhs) = delete;

};