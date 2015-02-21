#include "RocketSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "RocketSpellDelegate.h"

RocketSpell::RocketSpell(void)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_delegate = NULL;
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
	if (_delegate)
	{
		_delegate->removeCurrentDetail();
	}
	_currentDetailDataSource->removeCurrentDetail();
}

void RocketSpell::setDelegate(RocketSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}