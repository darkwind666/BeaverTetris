#include "GameLevelsMenuDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameKeyWithSuffixSupporter.h"
#include "GameStatesHelper.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "GameViewElementsDataSource.h"
#include "GameEnums.h"

using namespace std;
using namespace cocos2d;

const string lockedLevel = string("Locked");

GameLevelsMenuDataSource::GameLevelsMenuDataSource()
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_gameLevelsDataSource = (GameLevelsDataSource*)ServiceLocator::getServiceForKey(gameLevelsDataSourceKey);
	_gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);

	_menuItems = makeMenuItems();
}


GameLevelsMenuDataSource::~GameLevelsMenuDataSource(void)
{
}


vector <string> GameLevelsMenuDataSource::makeMenuItems()
{
	vector <string> availableLevels = vector <string>();

	int availableLevelsCount = getAvailableLevelsCount();

	for (int i = 0; i < availableLevelsCount; i++)
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

	if (aIndex > _currentPlayerDataSource->getPlayerCompletedLevelsCount())
	{

		levelKey = GameKeyWithSuffixSupporter::makeLockedImageForKey(_menuItems[aIndex]);
	} 
	else
	{
	    levelKey = _menuItems[aIndex];
	}

	string levelImage = GameFileExtensionMaker::getGraphicWithExtension(levelKey);
	return levelImage;
}

Vec2 GameLevelsMenuDataSource::getLevelIconPositionForIndex(int aIndex)
{
	string levelKey = _menuItems[aIndex];
	Vec2 levelImagePosition = _gameViewElementsDataSource->getElementPositionForKey(levelKey);
	return levelImagePosition;
}

void GameLevelsMenuDataSource::selectGameLevelForIndex(int aIndex)
{
	_currentPlayerDataSource->setSelectedGameLevelIndex(aIndex);
	GameStatesHelper::goToScene(kPlayGame);
}


int GameLevelsMenuDataSource::getAvailableLevelsCount()
{
	int allLevelsCount = _gameLevelsDataSource->getLevelsCount();
	int completedLevelsCount = _currentPlayerDataSource->getPlayerCompletedLevelsCount();

	int availableLevelsCount = 0;
	
	if (allLevelsCount == completedLevelsCount)
	{
		availableLevelsCount = completedLevelsCount;
	}
	else
	{
		availableLevelsCount = completedLevelsCount + 1;
	}
	return availableLevelsCount;
}