#pragma once

#include "FileStructure.h"
#include "Inheritance.h"

struct GenData
{

	std::string className;
	std::string parentClass;
	FileStructure fileStructure;
	Inheritance inhAccessor;
	bool hasCpyCtor = false;
	bool hasAssigOp = false;
	bool willSkipDirCheck = false;
};

