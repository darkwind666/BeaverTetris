#include "SpellBox.h"
#include "GameEnums.h"

using namespace std;

SpellBox::SpellBox(SpellsFactory *aSpellsFactory, CurrentPlayerDataSource *aCurrentPlayerDataSource)
{
	_spellsFactory = aSpellsFactory;
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_spellsInformations = getSpellsInformation();
}


SpellBox::~SpellBox(void)
{
}

int SpellBox::getAvailableSpellsCount()
{
	return _spellsInformations.size;
}

string SpellBox::getSpellNameOnIndex(int aIndex)
{
	return _spellsInformations[aIndex].spellName;
}

int SpellBox::getSpellCostOnIndex(int aIndex)
{
	return _spellsInformations[aIndex].spellCost;
}

void SpellBox::useSpellOnIndex(int aIndex)
{

	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore;
	int spellCost = getSpellCostOnIndex(aIndex);
	bool spellAvailable = _spellsFactory->spellAvailable;

	if (spellCost <= currentPlayerScore && spellAvailable)
	{
		SpellType spellType = _spellsInformations[aIndex].spellType;
		_spellsFactory->useSpellForType(spellType);
		int newPlayerScore = currentPlayerScore - spellCost;
		_currentPlayerDataSource->setPlayerScore(newPlayerScore);

	}

	
}
	
vector<SpellInformation> SpellBox::getSpellsInformation()
{
	vector<SpellInformation> spellInformation;

	SpellInformation spell1;
	spell1.spellType = kSpell1;
	spell1.spellName = string("Spell1");
	spell1.spellCost = 100;

	SpellInformation spell2;
	spell2.spellType = kSpell2;
	spell2.spellName = string("Spell2");
	spell2.spellCost = 200;

	SpellInformation spell3;
	spell3.spellType = kSpell3;
	spell3.spellName = string("Spell3");
	spell3.spellCost = 300;

	SpellInformation spell4;
	spell4.spellType = kSpell4;
	spell4.spellName = string("Spell4");
	spell4.spellCost = 400;

	spellInformation.push_back(spell1);
	spellInformation.push_back(spell2);
	spellInformation.push_back(spell3);
	spellInformation.push_back(spell4);

	return spellInformation;

}
	

	