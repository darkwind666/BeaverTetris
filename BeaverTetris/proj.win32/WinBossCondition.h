#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class WinBossCondition :public VictoryConditionInterface
{
public:
	WinBossCondition(GameLevelInformation aLevelInformation);
	~WinBossCondition(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

};

