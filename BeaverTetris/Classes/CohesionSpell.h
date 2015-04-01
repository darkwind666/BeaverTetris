#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include "GameStructures.h"

class GameBoard;
class CohesionSpellDelegate;
class TetraminosFactory;

class CohesionSpell :public SpellInterface, public ServiceInterface
{
public:
	CohesionSpell(void);
	~CohesionSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

	void setDelegate(CohesionSpellDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	CohesionSpellDelegate *_delegate;
	TetraminosFactory *_tetraminosFactory;
	int _cohesionCount;

	void setNewTetraminoInBoard();
	bool availablePlaceForTetraminoInLine(int aLine);
	void placeNewTetraminoInLine(int aLine);
	void setNewTetraminoForPosition(GamePositionOnBoard aPosition);
	TetraminoType getRandomTetraminoType();
	void sendMessageToDelegateWithTetraminoPosition(GamePositionOnBoard aPosition);

};

