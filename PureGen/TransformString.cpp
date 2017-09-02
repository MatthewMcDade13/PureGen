#include "stdafx.h"
#include "TransformString.h"

void TransformString(std::string& str, int(*caseFunc)(int c))
{
	transform(str.begin(), str.end(), str.begin(), caseFunc);
}
