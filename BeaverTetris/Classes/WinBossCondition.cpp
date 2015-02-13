#include "WinBossCondition.h"
#include "BossEnvironmentFactory.h"
#include "BossInterface.h"
#include "QueenBoss.h"

using namespace std;

WinBossCondition::WinBossCondition(GameLevelInformation aLevelInformation)
{
	BossEnvironmentFactory bossEnvironmentFactory;
	bossEnvironmentFactory.makeBossEnvironment();
	_currentBoss = new QueenBoss();
}


WinBossCondition::~WinBossCondition(void)
{
	delete _currentBoss;
}

int WinBossCondition::getVictoryStateInformationCount(void)
{
	return _currentBoss->getVictoryStateInformationCount();
}

int WinBossCondition::getVictoryStateInformationForIndex(int aIndex)
{
	return _currentBoss->getVictoryStateInformationForIndex(aIndex);
}

string WinBossCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	return _currentBoss->getVictoryStateIconImageForIndex(aIndex);
}

bool WinBossCondition::playerWin(void)
{
	return _currentBoss->playerWin();
}

void WinBossCondition::update(void)
{
	_currentBoss->update();
}
