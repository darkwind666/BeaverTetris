#include "QueenBoss.h"
#include "Tetramino.h"
#include "BossWithOneTetraminoDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "TetraminosFactory.h"

using namespace std;

QueenBoss::QueenBoss(void)
{
	TetraminosFactory *tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
	Tetramino *bossTetramino = tetraminosFactory->getNewTetraminoWithType(kTetraminoBossQueen);
	bossTetramino->addObserver(this);
	_bossWithOneTetraminoDelegate = new BossWithOneTetraminoDelegate(bossTetramino);
}


QueenBoss::~QueenBoss(void)
{
	delete _bossWithOneTetraminoDelegate;
}

int QueenBoss::getVictoryStateInformationCount(void)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateInformationCount();
}

int QueenBoss::getVictoryStateInformationForIndex(int aIndex)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateInformationForIndex(aIndex);
}

string QueenBoss::getVictoryStateIconImageForIndex(int aIndex)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateIconImageForIndex(aIndex);
}

bool QueenBoss::playerWin(void)
{
	return _bossWithOneTetraminoDelegate->playerWin();
}

void QueenBoss::update(void)
{
	
}

void QueenBoss::tetraminoRemoving(Tetramino *aTetramino)
{
	_bossWithOneTetraminoDelegate->tetraminoRemoving();
}