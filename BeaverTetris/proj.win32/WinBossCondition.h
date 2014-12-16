#pragma once

#include "VictoryConditionInterface.h"
#include "TetraminoObserverInterface.h"
#include "GameStructures.h"
#include <vector>
#include "KeysForEnumsDataSource.h"

class WinBossCondition :public VictoryConditionInterface, TetraminoObserverInterface
{
public:
	WinBossCondition(GameLevelInformation aLevelInformation);
	~WinBossCondition(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);

	void tetraminoRemoving(Tetramino *aTetramino);

private:

	std::vector<Tetramino*> _bosses;
	KeysForEnumsDataSource *_keysForEnumsDataSource;

	std::vector<Tetramino*> getBossesFromLevel(GameLevelInformation aLevelInformation);
	void subscribeToBosses();

};

