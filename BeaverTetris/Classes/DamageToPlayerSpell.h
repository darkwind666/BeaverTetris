#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;
class ExplosionAnimationDelegate;

class DamageToPlayerSpell :public SpellInterface, public ServiceInterface
{
public:
	DamageToPlayerSpell(void);
	~DamageToPlayerSpell(void);

	virtual bool spellAvailable();
	virtual void castSpell();
	virtual void updateSpell();
	virtual float getSpellRechargePercent();

	void setDelegate(ExplosionAnimationDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	bool _someTetraminosWasRemoved;
	ExplosionAnimationDelegate *_delegate;

	std::vector<GamePositionOnBoard> getTetraminosForRemovingInLines(std::vector<int> aLines);
	void fillTetraminosRemovingWithTetraminosFromLine(std::vector<GamePositionOnBoard> &aPositions, int aLine);
	std::vector<GamePositionOnBoard> getTetraminosForRemovingInLine(int aLine);
	void sendMessagesToDelegateWithTetraminosPositions(std::vector<GamePositionOnBoard> aPositions);
	void removeTetramninos(std::vector<GamePositionOnBoard> aPositions);

	std::vector<int> getLinesWithUnpeacefulCount();
	std::vector<GamePositionOnBoard> getUnEmptyAndNoBossesTetraminosInLine(int aLine);

};

