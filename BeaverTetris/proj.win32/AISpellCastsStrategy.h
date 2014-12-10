#pragma once

#include "AIStrategyInterface.h"
#include "SpellsFactory.h"


class AISpellCastsStrategy : public AIStrategyInterface
{
public:
	AISpellCastsStrategy(SpellsFactory *aSpellsFactory);
	~AISpellCastsStrategy(void);

	void updateAI();

private:

	SpellsFactory *_spellsFactory;
	int _currentUpdateState;

};

