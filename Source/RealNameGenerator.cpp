#include "RealNameGenerator.h"

RealNameGenerator::RealNameGenerator(vector<string>& Names)
{
	RealNames = Names;
}

RName RealNameGenerator::GenerateName() const
{
	return PolishName(RealNames[GetRandomNumber(RealNames.size())]);
}

RName RealNameGenerator::GenerateCompleteName() const
{
	return RName();
}
