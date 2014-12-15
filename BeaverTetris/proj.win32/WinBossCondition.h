#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class WinBossCondition :public VictoryConditionInterface
{
public:
	WinBossCondition(LevelInformation aLevelInformation);
	~WinBossCondition(void);

	int getVictoryStateInformationCount(void);
	std::string getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

};

