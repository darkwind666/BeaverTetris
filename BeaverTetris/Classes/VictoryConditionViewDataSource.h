#pragma once

#include <string>
#include "cocos2d.h"

class CurrentVictoryConditionDataSource;
class GameViewElementsDataSource;
class VictoryConditionInterface;

class VictoryConditionViewDataSource
{
public:
	VictoryConditionViewDataSource(CurrentVictoryConditionDataSource *currentVictoryConditionDataSource);
	~VictoryConditionViewDataSource(void);

	int getVictoryConditionsCount(void);
	std::string getVictoryConditionIconImageForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionIconImagePositionForIndex(int aIndex);

	std::string getVictoryConditionInformationForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionInformationPositionForIndex(int aIndex);

private:

	VictoryConditionInterface *_currentVictoryCondition;
	GameViewElementsDataSource *_gameViewElementsDataSource;

};

