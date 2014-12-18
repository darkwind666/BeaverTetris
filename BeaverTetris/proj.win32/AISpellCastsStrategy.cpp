#include "AISpellCastsStrategy.h"
#include "GameDesignConstants.h"
#include "GameEnums.h"
#include "GameHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "SpellsFactory.h"


AISpellCastsStrategy::AISpellCastsStrategy()
{
	_spellsFactory = (SpellsFactory*)ServiceLocator::getServiceForKey(gameBoardKey);
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
		_spellsFactory->useSpellForType((SpellType)randomSpellType);
	}
}