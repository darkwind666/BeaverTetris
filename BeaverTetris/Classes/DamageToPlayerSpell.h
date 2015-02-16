#pragma once

#include "SpellInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;
class DamageToPlayerSpellDelegate;

class DamageToPlayerSpell :public SpellInterface
{
public:
	DamageToPlayerSpell(void);
	~DamageToPlayerSpell(void);

	virtual bool spellAvailable(void);
	virtual void castSpell();

	void setDelegate(DamageToPlayerSpellDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;
	DamageToPlayerSpellDelegate *_delegate;

	std::vector<GamePositionOnBoard> getTetraminosForRemovingInLines(std::vector<int> aLines);
	void fillTetraminosRemovingWithTetraminosFromLine(std::vector<GamePositionOnBoard> &aPositions, int aLine);
	std::vector<GamePositionOnBoard> getTetraminosForRemovingInLine(int aLine);
	void sendMessagesToDelegateWithTetraminosPositions(std::vector<GamePositionOnBoard> aPositions);
	void removeTetramninos(std::vector<GamePositionOnBoard> aPositions);

	std::vector<int> getLinesWithUnpeacefulCount();
	std::vector<GamePositionOnBoard> getUnEmptyAndNoBossesTetraminosInLine(int aLine);

};

