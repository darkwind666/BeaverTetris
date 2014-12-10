#pragma once

#include "SpellInterface.h"
#include "GameBoard.h"
#include <vector>

class RandomExplosionsSpell :public SpellInterface
{
public:
	RandomExplosionsSpell(void);
	~RandomExplosionsSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;

	void removeRandomTetraminoInAvailableTetraminos(std::vector <GamePositionOnBoard> &availableTetraminos);
	void removeDeathTetraminos();

};

