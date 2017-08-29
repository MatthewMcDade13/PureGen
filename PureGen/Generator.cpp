#include "stdafx.h"
#include "Generator.h"

#include <iostream>

Generator::Generator()
{ }

Generator::~Generator()
{
}

void Generator::GenerateTemplate()
{
	std::cout << "Class Name: " << className << std::endl;
	std::cout << "Parent Class: " << parentClass << std::endl;
}

int Generator::ParseCommandArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		return 1;
	}

	className = argv[1];

	// parentClass = argv[2];
	if (argc > 2)
	{
		return 0;
		// Check for arguments
	}
	else
	{
		// just create template for passed in class name
		struct stat buf;

		if (stat("./Header Files", &buf) != 0 || stat("./Source Files", &buf) != 0)
		{
			std::cout << "Header File or Source File Directory not found." << std::endl;
			std::cout << "Would you like to create these directories?" << std::endl;
			std::string input = "";
			std::cin >> input;

			std::transform(input.begin(), input.end(), input.begin(), tolower);
			

			if (input.compare("yes") == 0)
			{				
				#if defined(OS_WINDOWS)

				_mkdir("./Header Files");
				_mkdir("./Source Files");

				#elif defined(OS_LINUX) || defined(OS_APPLE)

				mkdir("./Header Files");
				mkdir("./Source Files");

				#endif				
			}
			else
			{
				GenerateTemplate();
			}
		}
		return 0;
	}
}
