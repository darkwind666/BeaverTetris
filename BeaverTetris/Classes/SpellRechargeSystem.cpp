#include "SpellRechargeSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "SpellBox.h"


SpellRechargeSystem::SpellRechargeSystem(void)
{
	_spellBox = (SpellBox*)ServiceLocator::getServiceForKey(spellBoxKey);
}


SpellRechargeSystem::~SpellRechargeSystem(void)
{
}

void SpellRechargeSystem::updateSystem(float deltaTime)
{
	_spellBox->updateAllSpells();
}
