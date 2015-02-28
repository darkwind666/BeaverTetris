#include "RemainSomeTimeCondition.h"
#include "GameViewElementsKeys.h"

using namespace std;

RemainSomeTimeCondition::RemainSomeTimeCondition(GameLevelInformation aLevelInformation)
{
	_remainTimes = aLevelInformation.remainTimes;
}


RemainSomeTimeCondition::~RemainSomeTimeCondition(void)
{
}

int RemainSomeTimeCondition::getVictoryStateInformationCount(void)
{
	return 1;
}
int RemainSomeTimeCondition::getVictoryStateInformationForIndex(int aIndex)
{
	return _remainTimes;
}

string RemainSomeTimeCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	return remainSomeTimeIconKey;
}

bool RemainSomeTimeCondition::playerWin(void)
{
	bool playerWin = false;
	
	if (_remainTimes <= 0)
	{
		playerWin = true;
	}
	return playerWin;
}

void RemainSomeTimeCondition::update(void)
{
	_remainTimes--;
}
