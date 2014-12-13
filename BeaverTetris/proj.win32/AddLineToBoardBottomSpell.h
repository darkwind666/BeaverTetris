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
	void addRowToBottom();
	bool checkEmptyTetraminosInBottom();
	void separateTetraminos();

};

