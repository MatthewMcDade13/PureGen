// PureGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"

int main(int argc, char* argv[])
{	
	std::vector<std::string> args(argv + 1, argc + argv);

	Generator gen;
	if (gen.ParseCommandArgs(args) != 0)
	{
		return 1;
	}

	return gen.GenerateTemplate();	
}

