#include "SpellBox.h"
#include "GameEnums.h"
#include "SpellInterface.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "AddLineToBoardBottomSpell.h"
#include "RocketSpell.h"
#include "RandomExplosionsSpell.h"

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
	RocketSpell *rocketSpell = new RocketSpell();
	removeCurrentDetail.spell = rocketSpell;
	ServiceLocator::setServiceForKey(rocketSpell, rocketSpellModelKey);
	spellInformation[removeCurrentDetailSpellKey] = removeCurrentDetail;

	SpellInformation  removeRandomTetraminos;
	removeRandomTetraminos.spell = new RandomExplosionsSpell();
	removeRandomTetraminos.spellCost = 200;
	spellInformation[removeRandomTetraminosSpellKey] = removeRandomTetraminos;

	SpellInformation firestorm;
	firestorm.spell = new AddLineToBoardBottomSpell();
	firestorm.spellCost = 300;
	spellInformation[firestormSpellKey] = firestorm;

	SpellInformation cohesion;
	cohesion.spell = new AddLineToBoardBottomSpell();
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
	return spell->spellAvailable();
}
	

	

	
