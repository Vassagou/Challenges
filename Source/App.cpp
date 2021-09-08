#include "App.h"

#include <fstream>
#include <sstream>

#include "NameGenerator.h"
#include "RealNameGenerator.h"
#include "FicticialNameGenerator.h"

const int MaxNameSize = 12;
const int MaxSyllabeSize = 5;
const int MinSyllabeSize = 1;

App::App(int argc, char* argv[])
{
	// Initialize settings

	if (argc == 1)
	{
		// Load conf.txt and setup
		ifstream ConfFile;
		ConfFile.open("conf.txt");

		if (!ConfFile) {
			cerr << "Unable to open file conf.txt";
			exit(1);   
		}


		string Line;
		while (getline(ConfFile, Line))
		{
			if (Line[0] != '/'){ // Ignore '/' starting lines

				GetKeyValueFromString(Line);
			}
		}

		CheckSettings();

		ConfFile.close();
	}
	else
	{
		// setup from command line arguments

		if (argc < 2 || argc > 3) 
		{
			cerr << "Input Format Error - Shoud be: namegenerator.exe -real=[true/false] [-lang=[es/en]]";
		}

		bSecondArgument = false;

		FirstArgument = argv[1];
		
		if (argc == 3) {
			SecondArgument = argv[2];
			bSecondArgument = true;
		}


		GetKeyValueFromString(FirstArgument);
		
		if (bSecondArgument) 
		{
			GetKeyValueFromString(SecondArgument);
		}

		CheckSettings();
	}

	// Load files

	if (bRealName) 
	{
		ifstream InputNamesFile;
		InputNamesFile.open(LangFileName);

		if (!InputNamesFile) {
			cerr << "Unable to open file " << LangFileName << endl;
			exit(1);
		}

		RealNames = GetStringsPerLine(InputNamesFile);
		InputNamesFile.close();
	}
	else 
	{

		ifstream InputSyllabesFile;
		InputSyllabesFile.open("inputsyllabes.txt");

		if (!InputSyllabesFile) {
			cerr << "Unable to open file inputsyllabes.txt";
			exit(1);
		}

		Syllabes = GetStringsPerLine(InputSyllabesFile);
		InputSyllabesFile.close();
	}

	// Name Geneartor creation

	if (bRealName)
	{
		nameGenerator = new RealNameGenerator(RealNames);
	}
	else 
	{
		nameGenerator = new FicticialNameGenerator(Syllabes);
	}
}

App::~App()
{
	delete nameGenerator;
	nameGenerator = nullptr;
}

void App::Execute()
{
	cout << nameGenerator->GenerateName() << endl;
}

void App::CheckSettings()
{

	if (!(CheckIsReal() && CheckLang()))
	{
		cerr << "Error value settings. Check conf.txt or command line values." << endl;
		exit(1);
	}
}

bool App::CheckIsReal()
{
	string RealValue = Settings["real"];

	if (RealValue == "true")
	{
		bRealName = true;
		return true;
	}
	else if (RealValue == "false")
	{
		bRealName = false;
		return true;
	}
	else
	{
		cerr << "Error configuration value: real" << endl;
		return false;
	}
}

bool App::CheckLang()
{
	string LangValue = Settings["lang"];

	if (LangValue == "es")
	{
		Lang = ELanguage::SPANISH;
		LangFileName = "ES_names.txt";

		return true;
	}
	else if (LangValue == "en")
	{
		Lang = ELanguage::ENGLISH;
		LangFileName = "EN_names.txt";

		return true;
	}
	else
	{
		if(!bRealName)
		{
			return true;
		}
		cerr << "Error configuration value: lang" << endl;
		return false;
	}
}

void App::GetKeyValueFromString(string& InLine)
{

	string Key, Value;
	size_t EqualPosition = InLine.find('=');

	size_t KeyBegin = 1;
	size_t KeyEnd = EqualPosition - 1;
	size_t ValueBegin = EqualPosition + 1;
	size_t ValueEnd = InLine.size() - EqualPosition;

	Key = InLine.substr(KeyBegin, KeyEnd);
	Value = InLine.substr(ValueBegin, ValueEnd);
	
	Settings.insert(pair<string, string>(Key, Value));
}

vector<string> App::GetStringsPerLine(ifstream& InputFile)
{
	vector<string> TempStrings;
	string Line;

	while (getline(InputFile, Line))
	{
		if (bRealName) 
		{
			if (!Line.empty() && (Line.size() < MaxNameSize))
			{
				TempStrings.push_back(Line);
			}
		}
		else 
		{
			if (!Line.empty() && (Line.size() <= MaxSyllabeSize) && (Line.size() >= MinSyllabeSize))
			{
				TempStrings.push_back(Line);
			}
		}

	}

	return TempStrings;
}
