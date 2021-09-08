#include "NameGenerator.h"

#include <algorithm>
#include <ctime>
#include <cstdlib>

NameGenerator::NameGenerator() {
	// Seeds RNG
	srand(time(NULL));


}

RName NameGenerator::PolishName(RName NameToPolish) const
{
	RName Temp = NameToPolish;
	Temp[0] = toupper(Temp[0]);
	return Temp;
}

int NameGenerator::GetRandomNumber(unsigned int FromZeroToThis) const
{
	return rand()%FromZeroToThis;
}

int NameGenerator::GetRandomNumberInRange(unsigned int Min, unsigned int Max) const
{
	return rand()%Max + Min;
}
