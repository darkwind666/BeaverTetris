#include "GameGraphicsDataSource.h"
#include "GameFileExtensionMaker.h"

using namespace std;

const string startGraphicName = string("StartGraphics");
const string gameStartMenuGraphicName = string("StartGraphics");


GameGraphicsDataSource::GameGraphicsDataSource(void)
{
	_startGraphic = GameFileExtensionMaker::getGraphicWithExtension(startGraphicName);
	 string graphicKeys[] = {startGraphicName,gameStartMenuGraphicName};
	 _graphicElementsCount = sizeof(graphicKeys) / sizeof(graphicKeys[0]);
	_graphics = GameFileExtensionMaker::getGraphicsFilesWithExtension(graphicKeys, _graphicElementsCount);
}


GameGraphicsDataSource::~GameGraphicsDataSource(void)
{
}

string GameGraphicsDataSource::getInitialGraphic() 
{
	return _startGraphic;
}

int GameGraphicsDataSource::getGraphicCount() 
{
	return _graphicElementsCount;
}

std::string GameGraphicsDataSource::getGraphicForIndex(int aIndex) 
{
	return _graphics[aIndex];
}