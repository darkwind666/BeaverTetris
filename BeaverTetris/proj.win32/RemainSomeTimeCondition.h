#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class RemainSomeTimeCondition :public VictoryConditionInterface
{
public:
	RemainSomeTimeCondition(GameLevelInformation aLevelInformation);
	~RemainSomeTimeCondition(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

private:

	int _remainTimes;

};

