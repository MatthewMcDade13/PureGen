#pragma once
#include "FileStructure.h"

using namespace std;

class PureBase
{
public:
	PureBase();
	~PureBase();

protected:
	int SetFileStructure(FileStructure& fileStructure, bool willSkipDirCheck = false);
};

