#pragma once

#include "AIStrategyInterface.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "GameStructures.h"
#include "GameEnums.h"

class AIMovementStrategy :public AIStrategyInterface
{
public:
	AIMovementStrategy(GameBoard *aGameBoard, Tetramino *aTetramino);
	~AIMovementStrategy(void);

	void update();

private:

	GameBoard *_gameBoard;
	Tetramino *_bossTetramino;

	int _currentUpdateState;
	Tetramino *_lastTetraminoInBossPlace;

	GamePositionOnBoard getNewBossPosition();
	void placeBossOnNewPosition(GamePositionOnBoard newBossPosition);
	GamePositionOnBoard getNewBossPositionForDirectionType(BossMovementType aMovementType);
	bool checkPossitionPossibility(GamePositionOnBoard aPossiblePosition);

};

