#pragma once

#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include <vector>
#include <map>
#include <functional>
#include "KeysForEnumsDataSource.h"

class BossInterface;

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

private:

	BossInterface *_currentBoss;

	BossInterface* getCurrentBossFromLevelInformation(GameLevelInformation aLevelInformation);
	std::map< TetraminoType, std::function<BossInterface*()> > getBossesFactoriesWithLevelData(GameLevelInformation aLevelInformation);

};

