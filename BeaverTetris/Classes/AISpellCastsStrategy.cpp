#include "AISpellCastsStrategy.h"
#include "GameDesignConstants.h"
#include "GameEnums.h"
#include "GameHelper.h"
#include "SpellInterface.h"

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

	return spells;
}