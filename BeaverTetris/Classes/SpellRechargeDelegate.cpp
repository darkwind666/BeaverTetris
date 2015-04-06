#include "SpellRechargeDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"

using namespace std;

SpellRechargeDelegate::SpellRechargeDelegate(string spellKey)
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_spellRechargeInterval = currentPlayerDataSource->getSpellRechargeIntervalForKey(spellKey);
	_rechargeState = 0;
}


SpellRechargeDelegate::~SpellRechargeDelegate(void)
{
}

void SpellRechargeDelegate::updateSpell()
{
	if (_rechargeState > 0)
	{
		_rechargeState--;
	}
}

float SpellRechargeDelegate::getSpellRechargePercent()
{
	float rechargePercent = 100.0f * _rechargeState / _spellRechargeInterval;
	return rechargePercent;
}

void SpellRechargeDelegate::spellWasCasted()
{
	_rechargeState = _spellRechargeInterval;
}

bool SpellRechargeDelegate::spellRecharged()
{
	bool recharged = (_rechargeState <= 0);
	return recharged;
}

