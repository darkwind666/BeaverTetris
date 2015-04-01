#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include "GameEnums.h"

class GameBoard;
class AddLineToBoardBottomSpellDelegate;
class TetraminosFactory;

class AddLineToBoardBottomSpell :public SpellInterface, public ServiceInterface
{
public:
	AddLineToBoardBottomSpell(void);
	~AddLineToBoardBottomSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

	void setDelegate(AddLineToBoardBottomSpellDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	AddLineToBoardBottomSpellDelegate *_delegate;
	TetraminosFactory *_tetraminosFactory;

	void riseAllTetraminos();
	void riseTetraminosLineInBoard(int aLineIndex);
	void riseTetraminoInBoardOnXY(int xPosition, int yPosition);
	void addRowToBottom();
	void fillBottomWithRandomTetraminos();
	TetraminoType getTetraminoTypeForXPosition(int xPosition);
	void makeGapInBottom();
	bool checkEmptyTetraminosInBottom();
	void separateTetraminos();

	void sendUpGameBoardMessageToDelegate();
	void sendAddLineMessageToDelegate();

};

