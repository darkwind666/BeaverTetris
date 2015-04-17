#pragma once

#include "ServiceInterface.h"
#include <string>
#include <vector>
#include "GameStructures.h"
#include "cocos2d.h"

class CurrentPlayerDataSource;
class GameLevelsDataSource;
class GameViewElementsDataSource;

class GameLevelsMenuDataSource :public ServiceInterface
{
public:
	GameLevelsMenuDataSource();
	~GameLevelsMenuDataSource(void);

	int getLevelsCount(void);
	std::string getLevelIconImageForIndex(int aIndex);
	std::string getCompletedLevelSignImage();
	cocos2d::Vec2 getLevelIconPositionForIndex(int aIndex);
	bool levelCompletedForIndex(int aIndex);
	cocos2d::Vec2 getLevelCompletedSignPositionForIndex(int aIndex);
	void selectGameLevelForIndex(int aIndex);

private:

	std::vector <std::string> _menuItems;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameLevelsDataSource *_gameLevelsDataSource;
	GameViewElementsDataSource *_gameViewElementsDataSource;

	std::vector <std::string> makeMenuItems();
	int getAvailableLevelsCount();

};

