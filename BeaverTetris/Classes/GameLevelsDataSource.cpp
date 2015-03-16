#include "GameLevelsDataSource.h"
#include "GameLevelsDataFactory.h"

using namespace std;

GameLevelsDataSource::GameLevelsDataSource(void)
{
	GameLevelsDataFactory gameLevelsDataFactory;
	_levelsInformation = gameLevelsDataFactory.getLevelsInformation();
}


GameLevelsDataSource::~GameLevelsDataSource(void)
{
}

int GameLevelsDataSource::getLevelsCount()
{
	return _levelsInformation.size();
}

string GameLevelsDataSource::getLevelNameForIndex(int aIndex)
{
	GameLevelInformation levelInformation = _levelsInformation[aIndex];
	return levelInformation.levelName;
}

GameLevelInformation GameLevelsDataSource::getLevelDataForIndex(int aIndex)
{
	return _levelsInformation[aIndex];
}