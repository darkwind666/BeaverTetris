#include "GameGraphicsDataSource.h"
#include "GameFileExtensionMaker.h"

using namespace std;

const string loadingScreenGraphicName = string("LoadingScreenTextureAtlas");
const string selectLevelGraphicName = string("SelectLevelScreenTextureAtlas");
const string mainGameGraphicName = string("MainGameScreenTextureAtlas");
const string finalScreenGraphicName = string("FinalScreenTextureAtlas");

GameGraphicsDataSource::GameGraphicsDataSource(void)
{
	_graphicsKeys = getGraphicKeys();
}

GameGraphicsDataSource::~GameGraphicsDataSource(void)
{
}

string GameGraphicsDataSource::getInitialGraphic() 
{
	return GameFileExtensionMaker::getGraphicWithExtension(loadingScreenGraphicName);
}

string GameGraphicsDataSource::getInitialGraphicFrame()
{
	return GameFileExtensionMaker::getGraphicFramesWithExtension(loadingScreenGraphicName);
}

int GameGraphicsDataSource::getGraphicCount() 
{
	return _graphicsKeys.size();
}

string GameGraphicsDataSource::getGraphicForIndex(int aIndex) 
{
	string graphicKey = _graphicsKeys[aIndex];
	return GameFileExtensionMaker::getGraphicWithExtension(graphicKey);
}

string GameGraphicsDataSource::getGraphicFrameForIndex(int aIndex)
{
	string graphicKey = _graphicsKeys[aIndex];
	return GameFileExtensionMaker::getGraphicFramesWithExtension(graphicKey);
}

std::vector<std::string> GameGraphicsDataSource::getGraphicKeys()
{
	vector<string> graphicsKeys;

	graphicsKeys.push_back(selectLevelGraphicName);
	graphicsKeys.push_back(mainGameGraphicName);
	graphicsKeys.push_back(finalScreenGraphicName);

	return graphicsKeys;
}