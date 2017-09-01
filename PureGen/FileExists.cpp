#include "stdafx.h"
#include "FileExists.h"
#include "FileExists.h"

bool FileExists(const std::string & filePath)
{
	struct stat buffer;
	return (stat(filePath.c_str(), &buffer) == 0);
}
