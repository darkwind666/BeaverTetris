#include "AISpellCastsStrategy.h"
#include "GameDesignConstants.h"
#include "GameEnums.h"
#include "GameHelper.h"


AISpellCastsStrategy::AISpellCastsStrategy(SpellBox *aSpellBox)
{
	_spellBox = aSpellBox;
	_currentUpdateState = 0;
}


AISpellCastsStrategy::~AISpellCastsStrategy(void)
{
}

void AISpellCastsStrategy::updateAI()
{
	if (_currentUpdateState >= tetraminoBossTimeIntervalSpellCastConstant)
	{
		_currentUpdateState = 0;
		int randomSpellType = kBadSpell + 1 + GameHelper::getRandomNumberFromUpInterval(kSpellEnd - kBadSpell - 1);
		_spellBox->useSpellOnType((SpellType)randomSpellType);
	}
}