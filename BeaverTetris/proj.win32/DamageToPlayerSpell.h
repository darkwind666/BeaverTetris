#pragma once
#include "SpellInterface.h"
class DamageToPlayerSpell :public SpellInterface
{
public:
	DamageToPlayerSpell(void);
	~DamageToPlayerSpell(void);

	bool spellAvailable(void);
	void castSpell();

};

