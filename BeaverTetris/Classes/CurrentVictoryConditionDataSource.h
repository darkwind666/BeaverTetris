#pragma once

#include "ServiceInterface.h"
#include "VictoryConditionInterface.h"

class CurrentLevelDataSource;

class CurrentVictoryConditionDataSource : public ServiceInterface
{
public:
	CurrentVictoryConditionDataSource();
	~CurrentVictoryConditionDataSource(void);

	VictoryConditionInterface* getCurrentVictoryCondition();

private:

	VictoryConditionInterface *_currentVictoryCondition;
	CurrentLevelDataSource *_currentLevelDataSource;

	VictoryConditionInterface* getVictoryCondition();

};

