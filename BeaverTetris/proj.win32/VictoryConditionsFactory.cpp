#include "VictoryConditionsFactory.h"
#include "PlaceSomeDetailsCondition.h"
#include "RemainSomeTimeCondition.h"
#include "RemoveSomeTetraminosCondition.h"
#include "WinBossCondition.h"

using namespace std;

VictoryConditionsFactory::VictoryConditionsFactory(CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelDataSource = aCurrentLevelDataSource;
	_victoryConditionsBuildFunctions = map<VictoryConditionType, victoryConditionBuildFunction>();
	_victoryConditionsBuildFunctions[kPlaceSomeDetailsCondition] = &VictoryConditionsFactory::makePlaceSomeDetailsCondition;
	_victoryConditionsBuildFunctions[kRemainSomeTimeCondition] = &VictoryConditionsFactory::makeRemainSomeTimeCondition;
	_victoryConditionsBuildFunctions[kRemoveSomeTetraminosCondition] = &VictoryConditionsFactory::makeRemoveSomeTetraminosCondition;
	_victoryConditionsBuildFunctions[kWinBossCondition] = &VictoryConditionsFactory::makeWinBossCondition;
}


VictoryConditionsFactory::~VictoryConditionsFactory(void)
{
}

VictoryConditionInterface* VictoryConditionsFactory::makeCurrentVictoryCondition()
{
	_currentLevelInformation = _currentLevelDataSource->getCurrentLevelData;
	victoryConditionBuildFunction makeCurrentVictoryConditionBuilder = _victoryConditionsBuildFunctions[_currentLevelInformation.victoryCondition];
	VictoryConditionInterface *currentVictoryCondition = (this->*makeCurrentVictoryConditionBuilder)();
	return currentVictoryCondition;
}

VictoryConditionInterface* VictoryConditionsFactory::makePlaceSomeDetailsCondition()
{
	return new PlaceSomeDetailsCondition(_currentLevelInformation);
}

VictoryConditionInterface* VictoryConditionsFactory::makeRemainSomeTimeCondition()
{
	return new RemainSomeTimeCondition(_currentLevelInformation);
}

VictoryConditionInterface* VictoryConditionsFactory::makeRemoveSomeTetraminosCondition()
{
	return new RemoveSomeTetraminosCondition(_currentLevelInformation);
}

VictoryConditionInterface* VictoryConditionsFactory::makeWinBossCondition()
{
	return new WinBossCondition(_currentLevelInformation);
}
