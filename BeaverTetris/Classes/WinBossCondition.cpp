#include "WinBossCondition.h"

using namespace std;

WinBossCondition::WinBossCondition(GameLevelInformation aLevelInformation)
{
	
}


WinBossCondition::~WinBossCondition(void)
{
}

int WinBossCondition::getVictoryStateInformationCount(void)
{
	return 1;
}

int WinBossCondition::getVictoryStateInformationForIndex(int aIndex)
{
	return 2;
}

string WinBossCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	return string();
}

bool WinBossCondition::playerWin(void)
{
	return false;
}

void WinBossCondition::update(void)
{

}
