#pragma once

#include "SpellInterface.h"
#include "GameBoard.h"

class DamageToPlayerSpell :public SpellInterface
{
public:
	DamageToPlayerSpell(void);
	~DamageToPlayerSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;

	std::vector<int> getLinesWithUnpeacefulCount();
	std::vector<GamePositionOnBoard> getUnEmptyAndNoBossesTetraminosInLine(int aLine);
	void makeReductionInLine(int aLine);

	void separateTetraminos();

};

