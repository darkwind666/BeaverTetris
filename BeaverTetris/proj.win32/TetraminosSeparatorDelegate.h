#pragma once

#include "GameBoard.h"
#include "ActiveDetails.h"

class TetraminosSeparatorDelegate
{
public:
	TetraminosSeparatorDelegate(GameBoard *aGameBoard, ActiveDetails *aActiveDetails);
	~TetraminosSeparatorDelegate(void);

	void separateTetraminos();

private:

	GameBoard *_gameBoard;
	ActiveDetails *_activeDetails;

};

