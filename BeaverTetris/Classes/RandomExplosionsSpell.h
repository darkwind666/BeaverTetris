#pragma once

#include "SpellInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include "GameStructures.h"

class GameBoard;
class ExplosionAnimationDelegate;
class SpellRechargeDelegate;

class RandomExplosionsSpell :public SpellInterface, public ServiceInterface
{
public:
	RandomExplosionsSpell(void);
	~RandomExplosionsSpell(void);

	virtual bool spellAvailable();
	virtual void castSpell();
	virtual void updateSpell();
	virtual float getSpellRechargePercent();

	void setDelegate(ExplosionAnimationDelegate *aDelegate);

private:

	GameBoard *_gameBoard;
	ExplosionAnimationDelegate *_delegate;
	int _randomExplosionsCount;
	SpellRechargeDelegate *_spellRechargeDelegate;

	std::vector <GamePositionOnBoard> getTetraminosForExplosion();
	void reduceLivesInTetraminos(std::vector <GamePositionOnBoard> aTetraminos);
	void sendMessageToDelegateWithTetraminos(std::vector <GamePositionOnBoard> aTetraminos);
	void sendDelegateKilledTetraminos(std::vector <GamePositionOnBoard> aTetraminos);
	void removeKilledTetraminos(std::vector <GamePositionOnBoard> aTetraminos);

};

