#pragma once

#include <string>

class SpellBox
{
public:
	SpellBox(void);
	~SpellBox(void);

	int getAvailableSpellsCount();
	std::string getSpellNameOnIndex(int aIndex);
	int getSpellCostOnIndex(int aIndex);
	void useSpellOnIndex(int aIndex);

};

