#pragma once

#include <string>
#include <vector>
#include "GameStructures.h"
#include "SpellsFactory.h"
#include "CurrentPlayerDataSource.h"

class SpellBox
{
public:
	SpellBox(SpellsFactory *aSpellsFactory, CurrentPlayerDataSource *aCurrentPlayerDataSource);
	~SpellBox(void);

	int getAvailableSpellsCount();
	std::string getSpellNameOnIndex(int aIndex);
	int getSpellCostOnIndex(int aIndex);
	void useSpellOnIndex(int aIndex);

private:

	SpellsFactory *_spellsFactory;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	std::vector<SpellInformation> _spellsInformations;

	std::vector<SpellInformation> getSpellsInformation();

};

