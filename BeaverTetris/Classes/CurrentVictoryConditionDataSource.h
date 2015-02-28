#pragma once

#include "ServiceInterface.h"
#include <map>
#include <functional>
#include "GameEnums.h"
#include "GameStructures.h"

class CurrentLevelDataSource;
class VictoryConditionInterface;

class CurrentVictoryConditionDataSource : public ServiceInterface
{
public:
	CurrentVictoryConditionDataSource();
	~CurrentVictoryConditionDataSource(void);

	VictoryConditionInterface* getCurrentVictoryCondition();

private:

	VictoryConditionInterface *_currentVictoryCondition;

	VictoryConditionInterface* getVictoryConditionWithLevelData(GameLevelInformation data);
	std::map< VictoryConditionType, std::function<VictoryConditionInterface*(GameLevelInformation)> > getVictoryConditions();
};

