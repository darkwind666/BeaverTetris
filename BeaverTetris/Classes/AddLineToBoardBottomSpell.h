#pragma once

#include "SpellInterface.h"
#include "GameBoard.h"

class AddLineToBoardBottomSpell :public SpellInterface
{
public:
	AddLineToBoardBottomSpell(void);
	~AddLineToBoardBottomSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;

	void riseAllTetraminos();
	void riseTetraminosLineInBoard(int aLineIndex);
	void riseTetraminoInBoardOnXY(int xPosition, int yPosition);
	void addRowToBottom();
	void fillBottomWithRandomTetraminos();
	void makeGapInBottom();
	bool checkEmptyTetraminosInBottom();
	void separateTetraminos();

};

