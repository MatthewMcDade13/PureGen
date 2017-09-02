#include "stdafx.h"
#include "GetUserInput.h"
#include "TransformString.h"


string GetUserInput(const string& message, bool isDecision, const vector<string>& answers)
{
	string input = "";

	if (isDecision)
	{
		do
		{

			cout << message + "(y/n):";
			getline(cin, input);
			TransformString(input, tolower);

		} while (find(answers.begin(), answers.end(), input) == answers.end());
	}
	else
	{
		cout << message << endl;
		getline(cin, input);
	}

	return input;
}