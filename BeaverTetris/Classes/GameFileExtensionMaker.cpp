#include "GameFileExtensionMaker.h"
#include "GameResourcesExtension.h"

using namespace std;

GameFileExtensionMaker::GameFileExtensionMaker(void)
{
}


GameFileExtensionMaker::~GameFileExtensionMaker(void)
{
}


string GameFileExtensionMaker::getGraphicWithExtension(string aGraphicKey) 
{
	string graphicFileWithExtension = aGraphicKey + graphicFileExtension;
	return graphicFileWithExtension;
}

string* GameFileExtensionMaker::getGraphicsFilesWithExtension(string *aGraphicsKeys, int arraySize) 
{
	pointerToFunction pointer = &getGraphicWithExtension;
	string *newStringArray = GameFileExtensionMaker::getFilesWithExtension(aGraphicsKeys,arraySize,pointer);
	return newStringArray;

}

string GameFileExtensionMaker::getSoundWithExtension(std::string aSoundKey)
{
	string graphicFileWithExtension = aSoundKey + soundFileExtension;
	return graphicFileWithExtension;
}

string* GameFileExtensionMaker::getSoundFilesWithExtension(std::string *aSoundKey, int arraySize) 
{
	pointerToFunction pointer = &getSoundWithExtension;
	string *newStringArray = GameFileExtensionMaker::getFilesWithExtension(aSoundKey,arraySize,pointer);
	return newStringArray;
}

string GameFileExtensionMaker::getConfigurationWithExtension(std::string aConfigurationKey)
{
	string graphicFileWithExtension = aConfigurationKey + configurationFileExtension;
	return graphicFileWithExtension;
}

string* GameFileExtensionMaker::getConfigurationFilesWithExtension(std::string *aConfigurationKey, int arraySize) 
{
	pointerToFunction pointer = &getConfigurationWithExtension;
	string *newStringArray = GameFileExtensionMaker::getFilesWithExtension(aConfigurationKey,arraySize,pointer);
	return newStringArray;
}




string* GameFileExtensionMaker::getFilesWithExtension(string *aGraphicsKeys, int arraySize, pointerToFunction aFunction) 
{

	string *newStringArray = new string[arraySize];
	int index = 0;

	for (string *i = aGraphicsKeys; i < (aGraphicsKeys + arraySize*sizeof(string)); i++)
	{
		index++;
		string newString = aFunction(*i);
		newStringArray[index] = newString;
	}

	return newStringArray;

}
