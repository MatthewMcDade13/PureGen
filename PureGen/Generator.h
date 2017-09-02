#pragma once

#include "GenData.h"
#include "PureBase.h"
#include "FileStructure.h"
#include "FileExtension.h"
#include "Inheritance.h"

using namespace std;

class Generator : PureBase
{
private:
	string className;
	string parentClass;
	FileStructure fileStructure;
	Inheritance inhAccessor;
	bool hasCpyCtor = false;
	bool hasAssigOp = false;
	bool willSkipDirCheck = false;

	int GenerateHeader();
	int GenerateCPP();	
	bool CheckFlag(const string& arg, const string& flag);
	int SaveFile(ofstream& file, const string text);
	int OpenFile(ofstream& file, FileExtension ext);

public:
	Generator();
	Generator(const GenData& data);		
	~Generator();

	int GenerateTemplate();
	
	int ParseCommandArgs(vector<string> args);


private:
	Generator(const Generator& other) = delete;
	Generator& operator=(const Generator& rhs) = delete;

};