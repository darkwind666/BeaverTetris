#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"

class RemainSomeTimeCondition :public VictoryConditionInterface
{
public:
	RemainSomeTimeCondition(GameLevelInformation aLevelInformation);
	~RemainSomeTimeCondition(void);

	virtual int getVictoryStateInformationCount(void);
	virtual int getVictoryStateInformationForIndex(int aIndex);
	virtual std::string getVictoryStateIconImageForIndex(int aIndex);
	
	virtual bool playerWin(void);
	virtual void update(void);

private:

	int _remainTimes;

};

