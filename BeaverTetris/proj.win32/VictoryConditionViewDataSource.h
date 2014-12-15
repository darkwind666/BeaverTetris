#pragma once

#include <string>
#include "cocos2d.h"
#include "VictoryConditionsFactory.h"
#include "PlayerSelectionDataSource.h"

class VictoryConditionViewDataSource
{
public:
	VictoryConditionViewDataSource(VictoryConditionsFactory *aGameVictoryFactory, PlayerSelectionDataSource *aPlayerSelectionDataSource);
	~VictoryConditionViewDataSource(void);

	int getVictoryConditionsCount(void);
	std::string getVictoryConditionIconImageForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionIconImagePositionForIndex(int aIndex);

	std::string getVictoryConditionInformationForIndex(int aIndex);
	cocos2d::Vec2 getVictoryConditionInformationPositionForIndex(int aIndex);

	void refreshDataSource();

private:

	VictoryConditionsFactory *_gameVictoryFactory;
	PlayerSelectionDataSource *_playerSelectionDataSource;
	VictoryConditionInterface *_currentVictoryCondition;

};

