#pragma once

#include "VictoryCondition.h"

class GameVictoryFactory
{
public:
	GameVictoryFactory(void);
	~GameVictoryFactory(void);

	VictoryCondition* makeVictoryConditionForLevelIndex(int aIndex);

};

