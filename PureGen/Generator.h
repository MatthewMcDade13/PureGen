#pragma once

#include "FileStructure.h"
#include "FileExtension.h"

class Generator
{
private:
	std::string className;
	std::string parentClass;
	FileStructure fileStructure;

	int GenerateHeader();
	int GenerateCPP();
	void OpenFile(std::ofstream& file, FileExtension ext);
	int SaveFile(std::ofstream& file, const std::string text);

public:
	Generator();	
	~Generator();

	int GenerateTemplate();
	int CheckDirectories();
	int ParseCommandArgs(int argc, char* argv[]);


private:
	Generator(const Generator& other) = delete;
	Generator& operator=(const Generator& rhs) = delete;

};