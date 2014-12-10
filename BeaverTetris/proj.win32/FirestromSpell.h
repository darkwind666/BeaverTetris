#pragma once

#include "SpellInterface.h"
#include "GameBoard.h"

class FirestromSpell :public SpellInterface
{
public:
	FirestromSpell(void);
	~FirestromSpell(void);

	bool spellAvailable(void);
	void castSpell();

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;

	void makeExplosionOnPositionXY(int positionX, int positionY);
	void runFireballWithXPosition(int positionX);
	void removeDeathTetraminos();

};

