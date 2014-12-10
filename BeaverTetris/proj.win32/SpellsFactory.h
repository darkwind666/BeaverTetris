#pragma once

#include "GameEnums.h"
#include "SpellInterface.h"
#include <map>

class SpellsFactory
{
public:
	SpellsFactory(void);
	~SpellsFactory(void);

	void useSpellForType(SpellType aSpellType);
	bool spellAvailable(SpellType aSpellType);

private:

	std::map<SpellType, SpellInterface*> _spells;

	std::map<SpellType, SpellInterface*> makeSpells();

};

