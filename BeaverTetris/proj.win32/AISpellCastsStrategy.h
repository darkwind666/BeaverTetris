#pragma once

class SpellsFactory;

#include "AIStrategyInterface.h"

class AISpellCastsStrategy : public AIStrategyInterface
{
public:
	AISpellCastsStrategy();
	~AISpellCastsStrategy(void);

	void updateAI();

private:

	SpellsFactory *_spellsFactory;
	int _currentUpdateState;

};

