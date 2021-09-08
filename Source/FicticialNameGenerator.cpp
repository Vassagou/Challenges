#include "FicticialNameGenerator.h"


const int MaxSyllabesPerName = 3;
const int MinSyllabesPerName = 2;

FicticialNameGenerator::FicticialNameGenerator(vector<string> InSyllabes)
{

	// Populate syllabes
	Syllabes = InSyllabes;
}

RName FicticialNameGenerator::GenerateName() const
{
	RName TemporalName;

	const size_t ammountSyllabes = GetRandomNumberInRange(MinSyllabesPerName, MaxSyllabesPerName);

	for (size_t i = 0; i < ammountSyllabes; ++i)
	{
		TemporalName.append(GetRandomSyllave());
	}

	return PolishName(TemporalName);
}

RName FicticialNameGenerator::GenerateCompleteName() const
{
	return RName(GenerateName() + " " + GenerateName());
}

Syllave FicticialNameGenerator::GetRandomSyllave() const
{
	const size_t ammountSyllabes = Syllabes.size();

	return Syllabes[GetRandomNumber(ammountSyllabes)];
}

