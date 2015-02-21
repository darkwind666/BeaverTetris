#include "RocketSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"

RocketSpell::RocketSpell(void)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
}


RocketSpell::~RocketSpell(void)
{
}

bool RocketSpell::spellAvailable()
{
	return _currentDetailDataSource->currentDetailAvailable();
}

void RocketSpell::castSpell()
{
	_currentDetailDataSource->removeCurrentDetail();
}