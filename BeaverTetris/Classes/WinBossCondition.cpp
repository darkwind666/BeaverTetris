#include "WinBossCondition.h"
#include "BossEnvironmentFactory.h"
#include "BossInterface.h"
#include "QueenBoss.h"
#include "PrincessBoss.h"
#include "KingBoss.h"

using namespace std;

WinBossCondition::WinBossCondition(GameLevelInformation aLevelInformation)
{
	BossEnvironmentFactory bossEnvironmentFactory;
	bossEnvironmentFactory.makeBossEnvironment();
	_currentBoss = getCurrentBossFromLevelInformation(aLevelInformation);
}


WinBossCondition::~WinBossCondition(void)
{
	delete _currentBoss;
}

BossInterface* WinBossCondition::getCurrentBossFromLevelInformation(GameLevelInformation aLevelInformation)
{
	TetraminoType bossType = aLevelInformation.availableBosses.aBossType;
	map< TetraminoType, function<BossInterface*()> > bossesFactories = getBossesFactoriesWithLevelData(aLevelInformation);
	function<BossInterface*()> bossFactory = bossesFactories[bossType];
	BossInterface *currentBoss = bossFactory();
	return currentBoss;
}

map< TetraminoType, function<BossInterface*()> > WinBossCondition::getBossesFactoriesWithLevelData(GameLevelInformation aLevelInformation)
{
	map< TetraminoType, function<BossInterface*()> > bossesFactories;

	bossesFactories[kTetraminoBossQueen] = [](){
		BossInterface *queenBoss = new QueenBoss();
		return queenBoss;
	};

	bossesFactories[kTetraminoBossPrincess] = [aLevelInformation](){
		BossInterface *princessBoss = new PrincessBoss(aLevelInformation);
		return princessBoss;
	};

	bossesFactories[kTetraminoBossKing] = [aLevelInformation](){
		BossInterface *kingBoss = new KingBoss();
		return kingBoss;
	};

	return bossesFactories;
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
