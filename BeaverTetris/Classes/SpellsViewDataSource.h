#pragma once

#include <string>
#include "cocos2d.h"
#include "GameStructures.h"
#include <vector>

class SpellBox;
class CurrentPlayerDataSource;

class SpellsViewDataSource
{
public:
	SpellsViewDataSource();
	~SpellsViewDataSource(void);

	int getAvailableSpellsCount();
	std::string getSpellIconImageOnIndex(int aIndex);
	cocos2d::Vec2 getSpellPositionOnIndex(int aIndex);
	std::string getSpellCostOnIndex(int aIndex);
	int  getPlayerSpellKeyboardKeyOnIndex(int aIndex);
	void useSpellOnIndex(int aIndex);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	SpellBox *_spellBox;
	int _availableSpellsCount;
	cocos2d::Vec2 _spellOffset;

	std::vector<PlayerControllInformation> _spellsInformation;

	std::vector<PlayerControllInformation> makeSpellsInformation();
	bool spellAvailableForIndex(int aIndex);

};

