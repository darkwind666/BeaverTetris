#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "GameViewElementsDataSource.h"
#include "GameStructures.h"
#include "cocos2d.h"

class GameLevelsMenuDataSource :public ServiceInterface
{
public:
	GameLevelsMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, GameLevelsDataSource *aGameLevelsDataSource, GameViewElementsDataSource *aGameViewElementsDataSource);
	~GameLevelsMenuDataSource(void);

	int getLevelsCount(void);
	std::string getLevelIconImageForIndex(int aIndex);
	cocos2d::Vec2 getLevelIconPositionForIndex(int aIndex);
	GameEvent getLevelEventForIndex(int aIndex);

	void refreshDataSource();

private:

	std::vector <std::string> _menuItems;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameLevelsDataSource *_gameLevelsDataSource;
	GameViewElementsDataSource *_gameViewElementsDataSource;

	std::vector <std::string> makeMenuItems();

};

