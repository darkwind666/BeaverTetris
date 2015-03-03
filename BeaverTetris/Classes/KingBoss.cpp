#include "KingBoss.h"
#include "Tetramino.h"
#include "BossWithOneTetraminoDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "AIMovementStrategy.h"
#include "AISpellCastsStrategy.h"
#include "BossMovementObserver.h"

using namespace std;

KingBoss::KingBoss(void)
{
	Tetramino *bossTetramino = new Tetramino(kTetraminoBossKing, 3);
	bossTetramino->addObserver(this);
	_bossWithOneTetraminoDelegate = new BossWithOneTetraminoDelegate(bossTetramino);
	_movementStrategy = getMovementStrategeWithTetramino(bossTetramino);
	_spellCastsStrategy = new AISpellCastsStrategy();
}

KingBoss::~KingBoss(void)
{
	delete _bossWithOneTetraminoDelegate;
	delete _movementStrategy;
}

AIMovementStrategy* KingBoss::getMovementStrategeWithTetramino(Tetramino *aTetramino)
{
	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	AIMovementStrategy *movementStrategy = new AIMovementStrategy(gameBoard, aTetramino);
	BossMovementObserver *bossMovementObserver = (BossMovementObserver*)ServiceLocator::getServiceForKey(bossMovementObserverKey);
	movementStrategy->addObserver(bossMovementObserver);
	return movementStrategy;
}

int KingBoss::getVictoryStateInformationCount(void)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateInformationCount();
}

int KingBoss::getVictoryStateInformationForIndex(int aIndex)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateInformationForIndex(aIndex);
}

string KingBoss::getVictoryStateIconImageForIndex(int aIndex)
{
	return _bossWithOneTetraminoDelegate->getVictoryStateIconImageForIndex(aIndex);
}

bool KingBoss::playerWin(void)
{
	return _bossWithOneTetraminoDelegate->playerWin();
}

void KingBoss::update(void)
{
	_movementStrategy->updateAI();
	_spellCastsStrategy->updateAI();
}

void KingBoss::tetraminoRemoving(Tetramino *aTetramino)
{
	_bossWithOneTetraminoDelegate->tetraminoRemoving();
}