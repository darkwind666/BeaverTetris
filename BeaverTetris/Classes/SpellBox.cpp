#include "SpellBox.h"
#include "GameEnums.h"
#include "SpellInterface.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "RocketSpell.h"
#include "RandomExplosionsSpell.h"
#include "FirestromSpell.h"
#include "CohesionSpell.h"

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
	removeRandomTetraminos.spellCost = 200;
	RandomExplosionsSpell *randomExplosionsSpell = new RandomExplosionsSpell();
	removeRandomTetraminos.spell = randomExplosionsSpell;
	ServiceLocator::setServiceForKey(randomExplosionsSpell, randomExplosionsSpellModelKey);
	spellInformation[removeRandomTetraminosSpellKey] = removeRandomTetraminos;

	SpellInformation firestorm;
	firestorm.spellCost = 300;
	FirestromSpell *firestromSpell = new FirestromSpell();
	firestorm.spell = firestromSpell;
	ServiceLocator::setServiceForKey(firestromSpell, firestormSpellModelKey);
	spellInformation[firestormSpellKey] = firestorm;

	SpellInformation cohesion;
	cohesion.spellCost = 400;
	CohesionSpell *cohesionSpell = new CohesionSpell();
	cohesion.spell = cohesionSpell;
	ServiceLocator::setServiceForKey(cohesionSpell, cohesionSpellModelKey);
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
	

	

	
