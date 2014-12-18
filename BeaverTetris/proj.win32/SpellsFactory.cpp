#include "SpellsFactory.h"
#include "RocketSpell.h"
#include "RandomExplosionsSpell.h"
#include "FirestromSpell.h"
#include "CohesionSpell.h"
#include "DamageToPlayerSpell.h"
#include "AddLineToBoardBottomSpell.h"

using namespace std;

SpellsFactory::SpellsFactory(void)
{
	_spells = makeSpells();
}


SpellsFactory::~SpellsFactory(void)
{
}

bool SpellsFactory::spellAvailable(SpellType aSpellType)
{
	SpellInterface *spell = _spells[aSpellType];
	return spell->spellAvailable();
}

void SpellsFactory::useSpellForType(SpellType aSpellType)
{
	SpellInterface *spell = _spells[aSpellType];
	spell->castSpell();
}

map<SpellType, SpellInterface*> SpellsFactory::makeSpells()
{
	map<SpellType, SpellInterface*> spells;

	RocketSpell *rocketSpell = new RocketSpell();
	RandomExplosionsSpell *randomExplosionsSpell = new RandomExplosionsSpell();
	FirestromSpell *firestromSpell = new FirestromSpell();
	CohesionSpell *cohesionSpell = new CohesionSpell();
	DamageToPlayerSpell *damageToPlayerSpell = new DamageToPlayerSpell();
	AddLineToBoardBottomSpell *addLineToBoardBottomSpell = new AddLineToBoardBottomSpell();

	spells[kRocketSpell] = rocketSpell;
	spells[kRandomExplosionsSpell] = randomExplosionsSpell;
	spells[kFirestormSpell] = firestromSpell;
	spells[kAddLineToBoardBottomSpell] = addLineToBoardBottomSpell;
	spells[kDamageToPlayerSpell] = damageToPlayerSpell;

	return spells;

}