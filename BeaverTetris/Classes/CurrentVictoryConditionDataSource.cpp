#include "CurrentVictoryConditionDataSource.h"
#include "StringsSupporter.h"
#include "VictoryConditionInterface.h"
#include "WinBossCondition.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentLevelDataSource.h"

using namespace std;

CurrentVictoryConditionDataSource::CurrentVictoryConditionDataSource()
{
	_currentVictoryCondition = getVictoryCondition();
	_currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
}


CurrentVictoryConditionDataSource::~CurrentVictoryConditionDataSource(void)
{
}

VictoryConditionInterface* CurrentVictoryConditionDataSource::getCurrentVictoryCondition()
{
	return _currentVictoryCondition;
}

VictoryConditionInterface* CurrentVictoryConditionDataSource::getVictoryCondition()
{
	GameLevelInformation levelInformation = _currentLevelDataSource->getCurrentLevelData();
	return new WinBossCondition(levelInformation);
}