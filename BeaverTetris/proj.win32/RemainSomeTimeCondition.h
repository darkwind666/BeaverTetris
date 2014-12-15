#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class RemainSomeTimeCondition :public VictoryConditionInterface
{
public:
	RemainSomeTimeCondition(LevelInformation aLevelInformation);
	~RemainSomeTimeCondition(void);

	int getVictoryStateInformationCount(void);
	std::string getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

};

