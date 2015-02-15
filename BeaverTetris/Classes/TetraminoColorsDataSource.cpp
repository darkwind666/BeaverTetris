#include "TetraminoColorsDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

TetraminoColorsDataSource::TetraminoColorsDataSource(void)
{
	_tetraminosColors = getTetraminosColors();
}


TetraminoColorsDataSource::~TetraminoColorsDataSource(void)
{
}

map<string, Color3B> TetraminoColorsDataSource::getTetraminosColors()
{
	map<string, Color3B> tetraminosColors;

	tetraminosColors[redTetraminoKey] = Color3B::RED;
	tetraminosColors[greenTetraminoKey] = Color3B::GREEN;
	tetraminosColors[blueTetraminoKey] = Color3B::BLUE;
	tetraminosColors[goldTetraminoKey] = Color3B::YELLOW;
	tetraminosColors[blackTetraminoKey] = Color3B::BLACK;
	tetraminosColors[queenTetraminoKey] = Color3B::MAGENTA;
	tetraminosColors[princessTetraminoKey] = Color3B::GRAY;
	tetraminosColors[kingTetraminoKey] = Color3B::ORANGE;

	return tetraminosColors;
}

Color3B TetraminoColorsDataSource::getColorForKey(string aKey)
{
	string fileExtension = ".png";
	int fileExtensionPosition = aKey.find(fileExtension);
	string colorKey = aKey.erase(fileExtensionPosition, fileExtensionPosition + fileExtension.size());
	return _tetraminosColors[colorKey];
}