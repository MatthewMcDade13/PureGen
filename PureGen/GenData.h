#pragma once

#include "FileStructure.h"
#include "Inheritance.h"

using namespace std;

struct GenData
{
	string className;
	string parentClass;
	FileStructure fileStructure;
	Inheritance inhAccessor;
	bool hasCpyCtor = false;
	bool hasAssigOp = false;
	bool willSkipDirCheck = false;
};

