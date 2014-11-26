#include "GameLevelsMenuDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameEventsFactory.h"
#include "GameEnums.h"

using namespace std;
using namespace cocos2d;

const string newAvailableLevel = string("UnlockedLevel");

GameLevelsMenuDataSource::GameLevelsMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, GameLevelsDataSource *aGameLevelsDataSource, GameViewElementsDataSource *aGameViewElementsDataSource)
{
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_gameLevelsDataSource = aGameLevelsDataSource;
	_gameViewElementsDataSource = aGameViewElementsDataSource;

	_menuItems = makeMenuItems();
}


GameLevelsMenuDataSource::~GameLevelsMenuDataSource(void)
{
}


vector <string> GameLevelsMenuDataSource::makeMenuItems()
{

	vector <string> availableLevels = vector <string>();

	int completedLevelsCount = _currentPlayerDataSource->getPlayerCompletedLevelsCount();

	for (int i = 0; i < completedLevelsCount; i++)
	{
		string levelName = _gameLevelsDataSource->getLevelNameForIndex(i);
		availableLevels.push_back(levelName);
	}

	return availableLevels;

}


int GameLevelsMenuDataSource::getLevelsCount(void)
{
	return _menuItems.size();
}

string GameLevelsMenuDataSource::getLevelIconImageForIndex(int aIndex)
{
	string levelKey;

	if (aIndex > _currentPlayerDataSource->getPlayerCompletedLevelsCount)
	{
		levelKey = GameFileExtensionMaker::getGraphicWithExtension(newAvailableLevel);
	} 
	else
	{
	    levelKey = _menuItems[aIndex];
	}

	string levelImage = _gameViewElementsDataSource->getElementImageForKey(levelKey);
	return levelImage;
}

Vec2 GameLevelsMenuDataSource::getLevelIconPositionForIndex(int aIndex)
{
	string levelKey = _menuItems[aIndex];
	Vec2 levelImagePosition = _gameViewElementsDataSource->getElementPositionForKey(levelKey);
	return levelImagePosition;
}

GameEvent GameLevelsMenuDataSource::getLevelEventForIndex(int aIndex)
{
	return GameEventsFactory::makeGoToSceneEventWithKey(kPlayGame);
}

void GameLevelsMenuDataSource::refreshDataSource() 
{
	_menuItems = makeMenuItems();
}