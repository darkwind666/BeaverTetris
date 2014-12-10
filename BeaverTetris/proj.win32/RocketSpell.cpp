#include "RocketSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

RocketSpell::RocketSpell(void)
{
	_currentDetailController = (CurrentDetailController*)ServiceLocator::getServiceForKey(currentDetailControllerKey);
}


RocketSpell::~RocketSpell(void)
{
}

bool RocketSpell::spellAvailable()
{
	return _currentDetailController->availableCurrentDetail;
}

void RocketSpell::castSpell()
{
	_currentDetailController->removeCurrentDetail;
}