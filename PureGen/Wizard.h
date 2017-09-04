#pragma once
#include "GenData.h"
#include "PureBase.h"

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
	bool CheckYes(const std::string& input);
};

