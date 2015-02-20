#include "SpellBox.h"
#include "GameEnums.h"
#include "SpellInterface.h"
#include "GameViewElementsKeys.h"

using namespace std;

SpellBox::SpellBox()
{
	_spellsInformations = getSpellsInformation();
}


SpellBox::~SpellBox(void)
{
}

map<string, SpellInformation> SpellBox::getSpellsInformation()
{

	map<string, SpellInformation> spellInformation;

	SpellInformation removeCurrentDetail;
	removeCurrentDetail.spellCost = 100;
	spellInformation[removeCurrentDetailSpellKey] = removeCurrentDetail;

	SpellInformation  removeRandomTetraminos;
	removeRandomTetraminos.spellCost = 200;
	spellInformation[removeRandomTetraminosSpellKey] = removeRandomTetraminos;

	SpellInformation firestorm;
	firestorm.spellCost = 300;
	spellInformation[firestormSpellKey] = firestorm;

	SpellInformation cohesion;
	cohesion.spellCost = 400;
	spellInformation[cohesionSpellKey] = cohesion;

	return spellInformation;
}

int SpellBox::getSpellCostForKey(string aKey)
{
	return _spellsInformations[aKey].spellCost;
}

void SpellBox::useSpellForKey(string aKey)
{
	SpellInterface *spell = _spellsInformations[aKey].spell;
	spell->castSpell();
}

bool SpellBox::spellAvailableForKey(string aKey)
{
	SpellInterface *spell = _spellsInformations[aKey].spell;
	//return spell->spellAvailable();
	return true;
}
	

	

	
