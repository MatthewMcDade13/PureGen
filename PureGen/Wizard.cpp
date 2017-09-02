#include "stdafx.h"
#include "Wizard.h"
#include "GetUserInput.h"


Wizard::Wizard()
{
}


Wizard::~Wizard()
{
}

void Wizard::Start()
{
	vector<string> yn = { "y", "yes", "n", "no" };	
	string input;

	genData.className = GetUserInput("Enter Class Name: ");
	
	input = GetUserInput("Copy Constructor?", true, yn);	

	CheckYes(input) ? genData.hasCpyCtor = true : genData.hasCpyCtor = false;

	input = GetUserInput("Assignment Operator Overload?", true, yn);

	CheckYes(input) ? genData.hasAssigOp = true : genData.hasAssigOp = false;

	input = GetUserInput("Class inherits from base class?", true, yn);

	

	if (CheckYes(input))
	{

		vector<string> accessors = { "public", "private", "protected" };
		vector<string> parentClass = {};
		stringstream stream;
		string buf;
		do
		{
			
			stream.clear();
			parentClass.clear();

			cout << "Enter accessor for class followed by class name" << endl;
			getline(cin, input);
			
			stream.str(input); 

			while (stream >> buf)
			{
				parentClass.push_back(buf);
			}
			
			

		} while (find(accessors.begin(), accessors.end(), parentClass[0]) == accessors.end());

		string accessor = parentClass[0];
		genData.parentClass = parentClass[1];

		if (accessor.compare("private") == 0) genData.inhAccessor = Inheritance::Private;
		else if (accessor.compare("protected") == 0) genData.inhAccessor = Inheritance::Protected;
		else if (accessor.compare("public") == 0) genData.inhAccessor = Inheritance::Public;

	}

	SetFileStructure(genData.fileStructure);
	
}

GenData Wizard::GetGenData()
{
	return genData;
}

bool Wizard::CheckYes(const string & input)
{
	return (input.compare("y") == 0 || input.compare("yes") == 0);
}
