#pragma once

#include "GenData.h"
#include "PureBase.h"
#include "FileStructure.h"
#include "FileExtension.h"
#include "Inheritance.h"

class Generator : PureBase
{
private:

	std::string className;
	std::string parentClass;
	FileStructure fileStructure;
	Inheritance inhAccessor;
	bool hasCpyCtor = false;
	bool hasAssigOp = false;
	bool willSkipDirCheck = false;

	int GenerateHeader();
	int GenerateCPP();	
	bool CheckFlag(const std::string& arg, const std::string& flag);
	int SaveFile(std::ofstream& file, const std::string text);
	int OpenFile(std::ofstream& file, FileExtension ext);

public:
	Generator();
	Generator(const GenData& data);		
	~Generator();

	int GenerateTemplate();
	
	int ParseCommandArgs(std::vector<std::string> args);


private:
	Generator(const Generator& other) = delete;
	Generator& operator=(const Generator& rhs) = delete;

};