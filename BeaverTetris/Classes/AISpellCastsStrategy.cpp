#include "AISpellCastsStrategy.h"
#include "GameDesignConstants.h"
#include "GameEnums.h"
#include "GameHelper.h"
#include "SpellInterface.h"
#include "AddLineToBoardBottomSpell.h"

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
	if (_currentUpdateState >= 60)
	{
		_currentUpdateState = 0;
		castSpell();
	}
}

void AISpellCastsStrategy::castSpell()
{
	//int randomSpellIndex = GameHelper::getRandomNumberFromUpInterval(_spells.size() - 1);
	SpellInterface *spell = _spells[0];
	if (spell->spellAvailable())
	{
		spell->castSpell();
	}
}

vector<SpellInterface*> AISpellCastsStrategy::getSpells()
{
	vector<SpellInterface*> spells;

	SpellInterface *addLineToBoardBottomSpell = new AddLineToBoardBottomSpell();
	spells.push_back(addLineToBoardBottomSpell);

	return spells;
}