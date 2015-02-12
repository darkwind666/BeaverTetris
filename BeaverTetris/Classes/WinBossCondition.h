#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include <vector>
#include "KeysForEnumsDataSource.h"

class WinBossCondition :public VictoryConditionInterface
{
public:
	WinBossCondition(GameLevelInformation aLevelInformation);
	~WinBossCondition(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);

};

