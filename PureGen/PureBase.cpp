#include "stdafx.h"
#include "PureBase.h"
#include "TransformString.h"

PureBase::PureBase()
{
}


PureBase::~PureBase()
{
}


int PureBase::SetFileStructure(FileStructure& fileStructure, bool willSkipDirCheck)
{
	if (willSkipDirCheck == true)
	{
		fileStructure = FileStructure::Combined;
		return 0;
	}

	// just create template for passed in class name
	struct stat buf;

	if (stat("./HeaderFiles", &buf) != 0 || stat("./SourceFiles", &buf) != 0)
	{
		cout << "Header File or Source File Directory not found." << endl;
		cout << "Would you like to create these directories?(y/n): ";
		string input = "";
		cin >> input;

		// transform(input.begin(), input.end(), input.begin(), tolower);
		TransformString(input, tolower);


		if (input.compare("yes") == 0 || input.compare("y") == 0)
		{
			fileStructure = FileStructure::Separate;

			#if defined(OS_WINDOWS)

			if (_mkdir("./HeaderFiles") != 0 || _mkdir("./SourceFiles") != 0)
			{
				cout << "Failed to create Directories" << endl;
				return 1;
			}

			#elif defined(OS_LINUX) || defined(OS_APPLE)

			if (mkdir("./HeaderFiles") != 0 || mkdir("./SourceFiles") != 0)
			{
				cout << "Failed to create Directories" << endl;
				return 1;
			}

			#endif				
		}
		else
		{
			fileStructure = FileStructure::Combined;

			return 0;
		}
	}

	fileStructure = FileStructure::Separate;
	return 0;
}

