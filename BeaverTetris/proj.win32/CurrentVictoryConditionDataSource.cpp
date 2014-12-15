#include "CurrentVictoryConditionDataSource.h"

using namespace std;

CurrentVictoryConditionDataSource::CurrentVictoryConditionDataSource(CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelDataSource = aCurrentLevelDataSource;
	_victoryConditionsFactory = new VictoryConditionsFactory(aCurrentLevelDataSource);
	refreshDataSource();
}


CurrentVictoryConditionDataSource::~CurrentVictoryConditionDataSource(void)
{
}

int CurrentVictoryConditionDataSource::getVictoryConditionsCount(void)
{
	return _currentVictoryCondition->getVictoryStateInformationCount;
}

string CurrentVictoryConditionDataSource::getVictoryConditionNameForIndex(int aIndex)
{
	return _currentVictoryCondition->getVictoryStateIconImageForIndex(aIndex);
}

string CurrentVictoryConditionDataSource::getVictoryConditionInformationForIndex(int aIndex)
{
	return _currentVictoryCondition->getVictoryStateInformationForIndex(aIndex);
}
                          
void CurrentVictoryConditionDataSource::updateCurrentVictoryCondition()
{
	_currentVictoryCondition->update;
}

bool CurrentVictoryConditionDataSource::winGameResult()
{
	return _currentVictoryCondition->playerWin;
}

string CurrentVictoryConditionDataSource::getCurrentLevelName()
{
	return _currentLevelInformation.levelName;
}

int CurrentVictoryConditionDataSource::getCurrentLevelAward()
{
	return _currentLevelInformation.levelAward;
}

void CurrentVictoryConditionDataSource::refreshDataSource()
{
	_currentLevelInformation = _currentLevelDataSource->getCurrentLevelData;
	_currentVictoryCondition = _victoryConditionsFactory->makeCurrentVictoryCondition;
}