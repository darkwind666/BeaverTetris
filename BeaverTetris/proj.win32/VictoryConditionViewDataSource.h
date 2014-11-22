#pragma once

#include <string>
#include "cocos2d.h"

class VictoryConditionViewDataSource
{
public:
	VictoryConditionViewDataSource(void);
	~VictoryConditionViewDataSource(void);

	int getVictoryConditionsCount(void);
	std::string getVictoryConditionIconImageForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionIconImagePositionForIndex(int aIndex);

	std::string getVictoryConditionInformationForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionInformationForIndexPositionForIndex(int aIndex);


};

