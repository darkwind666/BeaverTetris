#include "AISpellCastsStrategy.h"
#include "GameDesignConstants.h"
#include "GameEnums.h"
#include "GameHelper.h"
#include "SpellInterface.h"
#include "AddLineToBoardBottomSpell.h"
#include "DamageToPlayerSpell.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;

AISpellCastsStrategy::AISpellCastsStrategy()
{
	_currentUpdateState = 0;
	_spells = getSpells();
}


AISpellCastsStrategy::~AISpellCastsStrategy(void)
{
}

void AISpellCastsStrategy::updateAI()
{
	_currentUpdateState++;
	if (_currentUpdateState >= tetraminoBossTimeIntervalSpellCastConstant)
	{
		_currentUpdateState = 0;
		castSpell();
	}
}

void AISpellCastsStrategy::castSpell()
{
	srand(time(0));
	int randomSpellIndex = GameHelper::getRandomNumberFromUpInterval(_spells.size());
	SpellInterface *spell = _spells[randomSpellIndex];
	if (spell->spellAvailable())
	{
		spell->castSpell();
	}
}

vector<SpellInterface*> AISpellCastsStrategy::getSpells()
{
	vector<SpellInterface*> spells;

	AddLineToBoardBottomSpell *addLineToBoardBottomSpell = new AddLineToBoardBottomSpell();
	ServiceLocator::setServiceForKey(addLineToBoardBottomSpell, addLineToBoardBottomSpellModelKey);
	spells.push_back(addLineToBoardBottomSpell);

	DamageToPlayerSpell *damageToPlayerSpell = new DamageToPlayerSpell();
	ServiceLocator::setServiceForKey(damageToPlayerSpell, damageToPlayerSpellModelKey);
	spells.push_back(damageToPlayerSpell);

	return spells;
}