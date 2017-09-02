#pragma once
#include "GenData.h"
#include "PureBase.h"

using namespace std;

class Wizard : PureBase
{
private:
	GenData genData;
public:

	Wizard();
	~Wizard();

	void Start();
	GenData GetGenData();

private:
	bool CheckYes(const string& input);
};

