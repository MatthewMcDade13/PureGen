// PureGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"

int main(int argc, char* argv[])
{	

	Generator gen;
	if (gen.ParseCommandArgs(argc, argv) != 0)
	{
		return 1;
	}

	return gen.GenerateTemplate();	
}

