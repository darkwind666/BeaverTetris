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
#include "CurrentLevelDataSource.h"
#include "CurrentPlayerDataSource.h"
#include "KeysForEnumsDataSource.h"

using namespace std;

SpellBox::SpellBox()
{
	setNewSpellsToPlayer();
	_spellsInformations = getSpellsInformation();
}


SpellBox::~SpellBox(void)
{
}

void SpellBox::setNewSpellsToPlayer()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	GameLevelInformation currentLevel = currentLevelDataSource->getCurrentLevelData();
	SpellType currentLevelSpellType = currentLevel.addSpell;
	if (currentLevelSpellType > kZeroSpell)
	{
		string spellKey = keysForEnumsDataSource->getKeyForSpellType(currentLevelSpellType);
		currentPlayerDataSource->setNewSpellForKey(spellKey);
	}
}

map<string, SpellInformation> SpellBox::getSpellsInformation()
{

	map<string, SpellInformation> spellInformation;

	SpellInformation removeCurrentDetail;
	removeCurrentDetail.spellCost = 60;
	RocketSpell *rocketSpell = new RocketSpell();
	removeCurrentDetail.spell = rocketSpell;
	ServiceLocator::setServiceForKey(rocketSpell, rocketSpellModelKey);
	spellInformation[removeCurrentDetailSpellKey] = removeCurrentDetail;

	SpellInformation firestorm;
	firestorm.spellCost = 120;
	FirestromSpell *firestromSpell = new FirestromSpell();
	firestorm.spell = firestromSpell;
	ServiceLocator::setServiceForKey(firestromSpell, firestormSpellModelKey);
	spellInformation[firestormSpellKey] = firestorm;

	SpellInformation  removeRandomTetraminos;
	removeRandomTetraminos.spellCost = 260;
	RandomExplosionsSpell *randomExplosionsSpell = new RandomExplosionsSpell();
	removeRandomTetraminos.spell = randomExplosionsSpell;
	ServiceLocator::setServiceForKey(randomExplosionsSpell, randomExplosionsSpellModelKey);
	spellInformation[removeRandomTetraminosSpellKey] = removeRandomTetraminos;

	SpellInformation cohesion;
	cohesion.spellCost = 310;
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
	

	

	
