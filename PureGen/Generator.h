#pragma once

#include <string>

class Generator
{
private:
	std::string className;
	std::string parentClass;


public:
	Generator();	
	~Generator();

	void GenerateTemplate();
	int ParseCommandArgs(int argc, char* argv[]);

private:
	Generator(const Generator& other) = delete;
	Generator& operator=(const Generator& rhs) = delete;

};