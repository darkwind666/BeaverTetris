#pragma once

#include "VictoryConditionInterface.h"
#include "CurrentLevelDataSource.h"
#include "GameEnums.h"
#include <map>

class VictoryConditionsFactory
{
public:
	VictoryConditionsFactory(CurrentLevelDataSource *aCurrentLevelDataSource);
	~VictoryConditionsFactory(void);

	VictoryConditionInterface* makeVictoryConditionForLevelIndex(int aIndex);

private:

	typedef VictoryConditionInterface* (VictoryConditionsFactory::*victoryConditionBuildFunction) ();

	CurrentLevelDataSource *_currentLevelDataSource;
	GameLevelInformation _currentLevelInformation;
	std::map<VictoryConditionType, victoryConditionBuildFunction> _victoryConditionsBuildFunctions;

	VictoryConditionInterface* makePlaceSomeDetailsCondition();
	VictoryConditionInterface* makeRemainSomeTimeCondition();
	VictoryConditionInterface* makeRemoveSomeTetraminosCondition();
	VictoryConditionInterface* makeWinBossCondition();

};

