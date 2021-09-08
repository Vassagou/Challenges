#pragma once

#include "NameGenerator.h"

using namespace std;

class RealNameGenerator :
    public NameGenerator
{
public:
    RealNameGenerator(vector<string>& Names);

    RName GenerateName() const override;

    RName GenerateCompleteName() const override;

private:
    std::vector<std::string> RealNames;
};

