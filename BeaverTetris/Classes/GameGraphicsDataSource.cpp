#include "GameGraphicsDataSource.h"
#include "GameFileExtensionMaker.h"

using namespace std;

const string startGraphicName = string("LoadingScreenTextureAtlas");
const string gameStartMenuGraphicName = string("MenuScreenTextureAtlas");

GameGraphicsDataSource::GameGraphicsDataSource(void)
{
	_graphicsKeys = getGraphicKeys();
}

GameGraphicsDataSource::~GameGraphicsDataSource(void)
{
}

string GameGraphicsDataSource::getInitialGraphic() 
{
	return GameFileExtensionMaker::getGraphicWithExtension(startGraphicName);
}

string GameGraphicsDataSource::getInitialGraphicFrame()
{
	return GameFileExtensionMaker::getGraphicFramesWithExtension(startGraphicName);
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

	graphicsKeys.push_back(gameStartMenuGraphicName);

	return graphicsKeys;
}