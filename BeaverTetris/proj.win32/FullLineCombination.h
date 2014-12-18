#pragma once

#include "GameBoard.h"
#include "CurrentPlayerDataSource.h"
#include "AwardForTetraminoDataSource.h"

class FullLineCombination
{
public:
	FullLineCombination(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~FullLineCombination(void);

	void checkFullLineCombination();

private:

	GameBoard *_gameBoard;
	AwardForTetraminoDataSource *_awardForTetraminoDataSource;
	CurrentPlayerDataSource *_currentPlayerDataSource;

	int getAwardForTetramino(Tetramino *aTetramino);

};

