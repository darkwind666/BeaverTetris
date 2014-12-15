#pragma once

#include <string>
#include "CurrentLevelDataSource.h"
#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include "VictoryConditionsFactory.h"

class CurrentVictoryConditionDataSource
{
public:
	CurrentVictoryConditionDataSource(CurrentLevelDataSource *aCurrentLevelDataSource);
	~CurrentVictoryConditionDataSource(void);

	int getVictoryConditionsCount(void);
	std::string getVictoryConditionNameForIndex(int aIndex);
	std::string getVictoryConditionInformationForIndex(int aIndex);

	void updateCurrentVictoryCondition();
	bool winGameResult();
	
	std::string getCurrentLevelName();
	int getCurrentLevelAward();

	void refreshDataSource();

private:

	CurrentLevelDataSource *_currentLevelDataSource;
	VictoryConditionInterface *_currentVictoryCondition;
	GameLevelInformation _currentLevelInformation;
	VictoryConditionsFactory *_victoryConditionsFactory;


};

