#pragma once

#include "SpellInterface.h"

class GameBoard;

class FirestromSpell :public SpellInterface
{
public:
	FirestromSpell(void);
	~FirestromSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

private:

	GameBoard *_gameBoard;

	void makeExplosionOnPositionXY(int positionX, int positionY);
	void runFireballWithXPosition(int positionX);
	void makeExplosionInRowAndExplosionX(int aRow, int explosionX);
	void removeDeathTetraminos();



};

