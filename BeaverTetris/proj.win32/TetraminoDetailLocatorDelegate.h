#pragma once

#include "GameBoard.h"
#include "TetraminoDetail.h"

class TetraminoDetailLocatorDelegate
{
public:
	TetraminoDetailLocatorDelegate(GameBoard *aGameBoard);
	~TetraminoDetailLocatorDelegate(void);

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

private:

	GameBoard *_gameBoard;

};

