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

string GameKeyWithSuffixSupporter::makeSelectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + selectedPrefix);
}

string GameKeyWithSuffixSupporter::makeUnselectedImageForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey + unselectedPrefix);
}

string GameKeyWithSuffixSupporter::makeLockedImageForKey(std::string aKey)
{
	return (aKey + lockedPrefix);
}

string GameKeyWithSuffixSupporter::makeRechargedImageForKey(string aKey)
{
	return (aKey + rechargedPrefix);
}