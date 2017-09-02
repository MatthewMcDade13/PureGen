// PureGen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Generator.h"
#include "Wizard.h"
#include "TransformString.h"
#include "GetUserInput.h"


using namespace std;


int main(int argc, char* argv[])
{	
	
	vector<string> args(argv + 1, argc + argv);

	string firstArg = args[0];

	TransformString(firstArg, tolower);

	if (firstArg.compare("wizard") == 0 || firstArg.compare("wiz") == 0)
	{
		Wizard wiz;
		wiz.Start();

		GenData data = wiz.GetGenData();
		Generator gen(data);

		return gen.GenerateTemplate();
	}
	else if (firstArg.compare("-v") == 0 || firstArg.compare("--version") == 0)
	{
		cout << "PureGen C++ Class Template Generator. v1.0.0" << endl;;
		return 0;
	}
	else
	{
		Generator gen;

		if (gen.ParseCommandArgs(args) != 0)
		{
			return 1;
		}

		return gen.GenerateTemplate();
	}

}

