#include "GameKeyWithSuffixSupporter.h"
#include "GameFileExtensionMaker.h"
#include "GameViewSuffixes.h"

using namespace std;

GameKeyWithSuffixSupporter::GameKeyWithSuffixSupporter(void)
{
}


GameKeyWithSuffixSupporter::~GameKeyWithSuffixSupporter(void)
{
}

void GameKeyWithSuffixSupporter::passImagesToMenuItemInformationWithKey(MenuItemInformation &aMenuItemInformation, string aKey)
{
	aMenuItemInformation.selectedImage = makeSelectedImageForKey(aKey);
	aMenuItemInformation.unselectedImage = makeUnselectedImageForKey(aKey);
}

string GameKeyWithSuffixSupporter::makeSelectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + selectedPrefix);
}

string GameKeyWithSuffixSupporter::makeUnselectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + unselectedPrefix);
}