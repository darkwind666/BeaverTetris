#pragma once

#include "CurrentPlayerDataSource.h"
#include "SpellBox.h"
#include <string>
#include "cocos2d.h"

class SpellsViewDataSource
{
public:
	SpellsViewDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, SpellBox *aSpellBox);
	~SpellsViewDataSource(void);

	int getAvailableSpellsCount();
	std::string getSpellIconImageOnIndex(int aIndex);
	cocos2d::Vec2 getSpellIconPositionOnIndex(int aIndex);
	std::string getSpellCostOnIndex(int aIndex);
	void useSpellOnIndex(int aIndex);

	void refreshDataSource();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	SpellBox *_spellBox;
	int _availableSpellsCount;
	cocos2d::Vec2 _startSpellIconsPositions;

};

