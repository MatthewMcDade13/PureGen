#include "stdafx.h"
#include "Generator.h"
#include "FileExists.h"

using namespace std;

Generator::Generator()
{ }

Generator::~Generator()
{
}

int Generator::GenerateHeader()
{
	ofstream file;

	if (OpenFile(file, FileExtension::Header) != 0)
	{
		return 1;
	}

	string text = "";
	string definition = className;
	string accessor = "";

	if (parentClass.size() > 0)
	{
		switch (inhAccessor)
		{
			case Inheritance::Public:
				accessor = "public";
				break;
			case Inheritance::Private:
				accessor = "private";
				break;
			case Inheritance::Protected:
				accessor = "protected";
				break;
		}
	}

	transform(definition.begin(), definition.end(), definition.begin(), toupper);

	text += "#ifndef " + definition + "\n";
	text += "#define " + definition + "\n\n";
	text += "class " + className;
	if (parentClass.size() > 0)
	{
		text += " : " + accessor + " " + parentClass + "\n";
	}
	text += "{\n";
	text += "private:\n";
	text += "public:\n";
	text += "\t" + className + "();\n";
	text += "\t~" + className + "();\n";

	if (hasCpyCtor) text += "\t" + className + "(const " + className + "& other);\n";
	if (hasAssigOp) text += "\t" + className + "& " + "operator=(const " + className + "& rhs);\n";

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

	if (OpenFile(file, FileExtension::Cpp) != 0)
	{
		return 1;
	}

	string text = "";	
	text += (string)"#include " + (string)"\"" + includePath + className + (string)".h\"\n\n";
	text += className + "::" + className + "()\n";
	text += "{\n\n}\n\n";
	text += className + "::" + '~' + className + "()\n";
	text += "{\n\n}\n\n";
	if (hasAssigOp)
	{
		text += className + "& " + className + "::operator=(const " + className + "& rhs)\n";
		text += "{\n";
		text += "\tif (this == &rhs) return *this;\n";
		text += "\treturn *this;\n";
		text += "}\n\n";
	}
	if (hasCpyCtor)
	{
		text += className + "::" + className + "(const " + className + "& other)\n";
		text += "{\n\n}\n\n";
	}
	text += '\n';

	if (SaveFile(file, text) != 0)
	{
		return 1;
	}
	return 0;
}

int Generator::OpenFile(ofstream& file, FileExtension ext)
{
	string extension = ext == FileExtension::Header ? ".h" : ".cpp";
	string folderName = ext == FileExtension::Header ? "./HeaderFiles/" : "./SourceFiles/";
	string filePath;

	if (fileStructure == FileStructure::Combined)
	{
		filePath = "./" + className + extension;		
	}
	else
	{
		filePath = folderName + className + extension;		
	}

	if (FileExists(filePath))
	{
		string input;

		cout << ("File " + filePath + " already exists.") << endl;
		cout << "Overwrite File?(y/n): ";
		cin >> input;

		transform(input.begin(), input.end(), input.begin(), tolower);

		if (input.compare("y") == 0 || input.compare("yes") == 0)
		{
			file.open(filePath.c_str());
			return 0;
		}
		else
		{
			return 1;
		}
		
	}

	file.open(filePath.c_str());
	return 0;
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

	fileStructure = FileStructure::Separate;
	return 0;
}

bool Generator::CheckFlag(const std::string & arg, const std::string & flag)
{
	return arg.compare(flag) == 0 && arg[0] == '-';
}

int Generator::ParseCommandArgs(int argc, char* argv[])
{
	vector<string> args(argv + 1, argv + argc);

	if (argc == 1)
	{
		cout << "No arguments given. Please at least specify Class Name." << endl;
		return 1;
	}

	className = args[0];

	// parentClass = argv[2];
	if (argc > 2)
	{
		string arg;
		for (size_t i = 1; i < args.size(); i++)
		{
			arg = args[i];
			;
			if (CheckFlag(arg, "-cc"))
			{
				hasCpyCtor = true;
				continue;
			}
			if (CheckFlag(arg, "-ao"))
			{
				hasAssigOp = true;
				continue;
			}
			if (CheckFlag(arg, "-nd"))
			{
				willSkipDirCheck = true;
				continue;
			}
			if (arg.find("-i") == 0 && arg[0] == '-')
			{
				if (i + 1 <= args.size() - 1)
				{
					
					if (args[i + 1].find('-') == -1)
					{
						if (arg.compare("-ipri") == 0) inhAccessor = Inheritance::Private;
						else if (arg.compare("-ipro") == 0) inhAccessor = Inheritance::Protected;
						else if (arg.compare("-ipub") == 0) inhAccessor = Inheritance::Public;
						else inhAccessor = Inheritance::Private;						

						parentClass = args[i + 1];
						continue;
					}
					else
					{
						cout << "Given value for inherit flag cannot be a flag or contain character '-'" << endl;
						return 1;
					}

				}
				else
				{
					cout << "No Parameter given for inheritor flag." << endl;
					return 1;
				}
			}
		}
		return CheckDirectories();		
	}
	else
	{
		return CheckDirectories();		
	}
}
