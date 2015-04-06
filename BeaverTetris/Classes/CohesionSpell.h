#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include "GameStructures.h"

class GameBoard;
class CohesionSpellDelegate;
class TetraminosFactory;
class SpellRechargeDelegate;

class CohesionSpell :public SpellInterface, public ServiceInterface
{
public:
	CohesionSpell(void);
	~CohesionSpell(void);

	virtual bool spellAvailable();
	virtual void castSpell();
	virtual void updateSpell();
	virtual float getSpellRechargePercent();

	void setDelegate(CohesionSpellDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	CohesionSpellDelegate *_delegate;
	TetraminosFactory *_tetraminosFactory;
	int _cohesionCount;
	SpellRechargeDelegate *_spellRechargeDelegate;

	void setNewTetraminoInBoard();
	bool availablePlaceForTetraminoInLine(int aLine);
	void placeNewTetraminoInLine(int aLine);
	void setNewTetraminoForPosition(GamePositionOnBoard aPosition);
	TetraminoType getRandomTetraminoType();
	void sendMessageToDelegateWithTetraminoPosition(GamePositionOnBoard aPosition);

};

