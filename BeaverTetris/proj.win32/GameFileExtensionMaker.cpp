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

	string *newStringArray = new string[arraySize];
	int index = 0;

	for (string *i = aGraphicsKeys; i < (aGraphicsKeys + arraySize*sizeof(string)); i++)
	{
		index++;
		string newString = getGraphicWithExtension(*i);
		newStringArray[index] = newString;
	}

	return newStringArray;

}
