#pragma once

#include "Types.h"


class NameGenerator
{
public:
	NameGenerator();

	~NameGenerator() {};

	virtual RName GenerateName() const = 0;

	virtual RName GenerateCompleteName() const = 0;

protected:
	virtual RName PolishName(RName NameToPolish) const;

	int GetRandomNumber(unsigned int FromZeroToThis) const;

	int GetRandomNumberInRange(unsigned int Min, unsigned int Max) const;
};

