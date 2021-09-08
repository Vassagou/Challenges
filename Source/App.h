#pragma once

#include "Types.h"

#include <map>

using namespace std;


enum class ELanguage {
	NONE,
	SPANISH,
	ENGLISH,
	SIZE
};


class App
{
public:
	App(int argc, char* argv[]);

	~App();

	void Execute();

private:
	void CheckSettings();

	bool CheckIsReal();

	bool CheckLang();

	void GetKeyValueFromString(string& InLine);

	vector<string> GetStringsPerLine(ifstream& InputFile);

private:
	// Settings
	bool bRealName;

	bool bSecondArgument;

	ELanguage Lang;

	string FirstArgument;

	string SecondArgument;

	map<string, string> Settings; // In memory configuration file

	vector<string> RealNames;

	string LangFileName;

	vector<string> Syllabes;

	// Representation

	class NameGenerator* nameGenerator;
};

