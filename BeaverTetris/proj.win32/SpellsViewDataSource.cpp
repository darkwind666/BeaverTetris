#include "SpellsViewDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameViewConstants.h"
#include "StringsSupporter.h"

using namespace std;
using namespace cocos2d;

SpellsViewDataSource::SpellsViewDataSource(CurrentPlayerDataSource *aCurrentPlayerDataSource, SpellBox *aSpellBox)
{
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_spellBox = aSpellBox;
	_availableSpellsCount = aCurrentPlayerDataSource->getPlayerAvailableSpellsCount;
}


SpellsViewDataSource::~SpellsViewDataSource(void)
{
}

int SpellsViewDataSource::getAvailableSpellsCount()
{
	return _availableSpellsCount;
}

string SpellsViewDataSource::getSpellIconImageOnIndex(int aIndex)
{
	return GameFileExtensionMaker::getGraphicWithExtension(_spellBox->getSpellNameOnIndex(aIndex));
}

Vec2 SpellsViewDataSource::getSpellIconPositionOnIndex(int aIndex)
{
	return Vec2(_startSpellIconsPositions.x, _startSpellIconsPositions.y + aIndex * spellIconsInterval);
}

string SpellsViewDataSource::getSpellCostOnIndex(int aIndex)
{
	int cost = _spellBox->getSpellCostOnIndex(aIndex);
	string stringCost = StringsSupporter::getStringFromNumber(cost);
	return stringCost;
}

void SpellsViewDataSource::useSpellOnIndex(int aIndex)
{
	int spellCost = _spellBox->getSpellCostOnIndex(aIndex);
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore;

	if (currentPlayerScore >= spellCost && aIndex <= _availableSpellsCount)
	{
		_currentPlayerDataSource->setPlayerScore(currentPlayerScore - spellCost);
		_spellBox->useSpellOnIndex(aIndex);
	}
	
}

void SpellsViewDataSource::refreshDataSource()
{
	_availableSpellsCount = _currentPlayerDataSource->getPlayerAvailableSpellsCount;
}
