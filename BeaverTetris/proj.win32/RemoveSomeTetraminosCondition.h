#pragma once

#include "GameBoardObserverInterface.h"
#include "VictoryConditionInterface.h"
#include "GameStructures.h"
#include "GameBoard.h"
#include <vector>
#include "KeysForEnumsDataSource.h"

class RemoveSomeTetraminosCondition :public VictoryConditionInterface, GameBoardObserverInterface
{
public:
	RemoveSomeTetraminosCondition(GameLevelInformation aLevelInformation);
	~RemoveSomeTetraminosCondition(void);

	int getVictoryStateInformationCount(void);
	int getVictoryStateInformationForIndex(int aIndex);
	std::string getVictoryStateIconImageForIndex(int aIndex);
	
	bool playerWin(void);
	void update(void);
	void tetraminoRemoving(Tetramino *aTetramino);

private:

	GameBoard *_gameBoard;
	std::vector<TetraminosForWinInformation> _tetraminosCollectionForWin;
	KeysForEnumsDataSource *_keysForEnumsDataSource;
};

