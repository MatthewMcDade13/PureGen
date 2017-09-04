#pragma once
#include "FileStructure.h"

class PureBase
{
public:
	PureBase();
	~PureBase();

protected:
	int SetFileStructure(FileStructure& fileStructure, bool willSkipDirCheck = false);
};

