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
#include "pugixml.hpp"
#include "GameBalanceDataConstants.h"

using namespace std;
using namespace pugi;

SpellBox::SpellBox()
{
	setNewSpellsToPlayer();
	_spellsCosts = getSpellsCosts();
	_spellsInformations = getSpellsInformation();
}


SpellBox::~SpellBox(void)
{
}

void SpellBox::setNewSpellsToPlayer()
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	map<string, int> spellsData = getSpellsData();
	map<string, int>::iterator spellsIterator;
	for (spellsIterator = spellsData.begin(); spellsIterator != spellsData.end(); spellsIterator++)
	{
		string spellType = spellsIterator->first;
		int spellCount = spellsIterator->second;
		currentPlayerDataSource->setNewSpellCountForKey(spellCount, spellType);
	}
}

map<string, int> SpellBox::getSpellsData()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	GameLevelInformation currentLevel = currentLevelDataSource->getCurrentLevelData();
	map<string, int> spellsData = currentLevel.spellsData;
	return spellsData;
}

map<string, int> SpellBox::getSpellsCosts()
{
	map<string, int> spellsCosts;
	map<TetraminoType, TetraminoInformation> tetraminosData;
	xml_document spellsFile;
	xml_parse_result result = spellsFile.load_file(gameSpellsFileKey.c_str());
	if (result)
	{
		xml_node spells = spellsFile.child(gameSpellsDataKey.c_str());
		for (xml_node spell = spells.first_child(); spell; spell = spell.next_sibling())
		{
			string spellType = spell.attribute(gameSpellTypeKey.c_str()).as_string();
			int spellCost = spell.attribute(gameSpellCostKey.c_str()).as_int();
			spellsCosts[spellType] = spellCost;
		}
	}
	return spellsCosts;
}

map<string, SpellInformation> SpellBox::getSpellsInformation()
{

	map<string, SpellInformation> spellInformation;

	SpellInformation removeCurrentDetail;
	removeCurrentDetail.spellCost = _spellsCosts[removeCurrentDetailSpellKey];
	RocketSpell *rocketSpell = new RocketSpell();
	removeCurrentDetail.spell = rocketSpell;
	ServiceLocator::setServiceForKey(rocketSpell, rocketSpellModelKey);
	spellInformation[removeCurrentDetailSpellKey] = removeCurrentDetail;

	SpellInformation firestorm;
	firestorm.spellCost = _spellsCosts[firestormSpellKey];
	FirestromSpell *firestromSpell = new FirestromSpell();
	firestorm.spell = firestromSpell;
	ServiceLocator::setServiceForKey(firestromSpell, firestormSpellModelKey);
	spellInformation[firestormSpellKey] = firestorm;

	SpellInformation  removeRandomTetraminos;
	removeRandomTetraminos.spellCost = _spellsCosts[removeRandomTetraminosSpellKey];
	RandomExplosionsSpell *randomExplosionsSpell = new RandomExplosionsSpell();
	removeRandomTetraminos.spell = randomExplosionsSpell;
	ServiceLocator::setServiceForKey(randomExplosionsSpell, randomExplosionsSpellModelKey);
	spellInformation[removeRandomTetraminosSpellKey] = removeRandomTetraminos;

	SpellInformation cohesion;
	cohesion.spellCost = _spellsCosts[cohesionSpellKey];
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
	

	

	
