#include "stdafx.h"
#include "Generator.h"

using namespace std;

Generator::Generator()
{ }

Generator::~Generator()
{
}

int Generator::GenerateHeader()
{
	ofstream file;

	OpenFile(file, FileExtension::Header);

	string text = "";
	string definition = className;

	transform(definition.begin(), definition.end(), definition.begin(), toupper);
	text += "#ifndef " + definition + "\n";
	text += "#define " + definition + "\n\n";
	text += "class " + className + "\n";
	text += "{\n";
	text += "private:\n";
	text += "public:\n";
	text += "\t" + className + "();\n";
	text += "\t~" + className + "();\n";
	text += "};\n\n";
	text += "#endif\n";

	if (SaveFile(file, text) != 0)
	{
		return 1;
	}
	return 0;
}

int Generator::GenerateCPP()
{
	string includePath = fileStructure == FileStructure::Combined ? "./" : "../HeaderFiles/";
	ofstream file;

	OpenFile(file, FileExtension::Cpp);

	string text = "";	
	text += (string)"#include " + (string)"\"" + includePath + className + (string)".h\"\n\n";
	text += className + "::" + className + "()\n";
	text += "{\n}\n";
	text += className + "::" + '~' + className + "()\n";
	text += "{\n}\n";
	text += '\n';

	if (SaveFile(file, text) != 0)
	{
		return 1;
	}
	return 0;
}

void Generator::OpenFile(ofstream& file, FileExtension ext)
{
	string extension = ext == FileExtension::Header ? ".h" : ".cpp";
	string folderName = ext == FileExtension::Header ? "./HeaderFiles/" : "./SourceFiles/";

	if (fileStructure == FileStructure::Combined)
	{
		string relativeFilePath = "./" + className + extension;
		file.open(relativeFilePath.c_str());
	}
	else
	{
		string headerFilePath = folderName + className + extension;
		file.open(headerFilePath.c_str());
	}
}

int Generator::SaveFile(std::ofstream & file, const std::string text)
{
	if (!(file << text))
	{
		cout << "Could not save to file" << endl;
		return 1;
	}
	else
	{
		file.close();
		return 0;
	}
}

int Generator::GenerateTemplate()
{
	if (GenerateHeader() != 0 || GenerateCPP() != 0)
	{
		return 1;
	}

	return 0;

}

int Generator::CheckDirectories()
{
	// just create template for passed in class name
	struct stat buf;	

	if (stat("./HeaderFiles", &buf) != 0 || stat("./SourceFiles", &buf) != 0)
	{
		cout << "Header File or Source File Directory not found." << endl;
		cout << "Would you like to create these directories?(y/n): ";
		string input = "";
		cin >> input;

		transform(input.begin(), input.end(), input.begin(), tolower);


		if (input.compare("yes") ==  0 || input.compare("y") == 0)
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

	return 0;
}

int Generator::ParseCommandArgs(int argc, char* argv[])
{
	if (argc == 1)
	{
		cout << "No arguments given. Please at least specify Class Name." << endl;
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
		return CheckDirectories();		
	}
}
