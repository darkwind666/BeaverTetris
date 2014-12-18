#include "GameLevelsDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

GameLevelsDataSource::GameLevelsDataSource(void)
{
	 string levelNames[] = {gameLevel1Key,gameLevel2Key,gameLevel3Key,gameLevel4Key,gameLevel5Key,gameLevel6Key,gameLevel7Key,gameLevel8Key,gameLevel9Key,gameLevel10Key};
	 _levelsCount = sizeof(levelNames) / sizeof(levelNames[0]);
	 _levelNames = new string[_levelsCount];

	 for (int i = 0; i < _levelsCount; i++)
	 {
		 _levelNames[i] = levelNames[i];
	 }
}


GameLevelsDataSource::~GameLevelsDataSource(void)
{
}


int GameLevelsDataSource::getLevelsCount()
{
	return _levelsCount;
}

string GameLevelsDataSource::getLevelNameForIndex(int aIndex)
{
	return _levelNames[aIndex];
}

LevelInformation GameLevelsDataSource::getLevelDataForIndex(int aIndex)
{
	LevelInformation levelInformation;
	return levelInformation;
}