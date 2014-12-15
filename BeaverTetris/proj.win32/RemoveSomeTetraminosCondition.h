#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class RemoveSomeTetraminosCondition :public VictoryConditionInterface
{
public:
	RemoveSomeTetraminosCondition(GameLevelInformation aLevelInformation);
	~RemoveSomeTetraminosCondition(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

};

