#pragma once

#include "NameGenerator.h"

using namespace std;


class FicticialNameGenerator :
    public NameGenerator
{
public:
    FicticialNameGenerator(vector<string> InSyllabes);

    RName GenerateName() const override;

    RName GenerateCompleteName() const override;

private:
    Syllave GetRandomSyllave() const;


private:
    std::vector<std::string> Syllabes;


};

