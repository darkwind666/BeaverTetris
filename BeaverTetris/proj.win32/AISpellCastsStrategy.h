#pragma once

#include "AIStrategyInterface.h"
#include "SpellBox.h"

class AISpellCastsStrategy : public AIStrategyInterface
{
public:
	AISpellCastsStrategy(SpellBox *aSpellBox);
	~AISpellCastsStrategy(void);

	void updateAI();

private:

	SpellBox *_spellBox;
	int _currentUpdateState;

};

