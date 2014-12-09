#pragma once

#include <string>
#include "GameEnums.h"

class SpellBox
{
public:
	SpellBox(void);
	~SpellBox(void);

	int getAvailableSpellsCount();
	std::string getSpellNameOnIndex(int aIndex);
	int getSpellCostOnIndex(int aIndex);
	SpellType getSpellTypeOnIndex(int aIndex);

	void useSpellOnType(SpellType aSpellType);

};

