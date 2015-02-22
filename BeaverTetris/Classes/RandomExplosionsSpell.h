#pragma once

#include "SpellInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;

class RandomExplosionsSpell :public SpellInterface
{
public:
	RandomExplosionsSpell(void);
	~RandomExplosionsSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;

	void removeRandomTetraminoInAvailableTetraminos(std::vector <GamePositionOnBoard> &availableTetraminos);
	void removeDeathTetraminos();

};

