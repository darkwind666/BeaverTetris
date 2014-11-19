#pragma once

#include <string>
#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "cocos2d.h"

class GameLevelsMenuDataSource
{
public:
	GameLevelsMenuDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, GameLevelsDataSource *aGameLevelsDataSource);
	~GameLevelsMenuDataSource(void);

	int getLevelsCount(void);
	std::string getLevelIconImageForIndex(int aIndex);
	cocos2d::Vec2 getLevelIconPositionForIndex(int aIndex);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameLevelsDataSource _gameLevelsDataSource;

};

