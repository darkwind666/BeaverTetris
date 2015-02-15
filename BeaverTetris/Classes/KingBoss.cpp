#include "KingBoss.h"
#include "Tetramino.h"
#include "BossWithOneTetraminoDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "AIMovementStrategy.h"
#include "AISpellCastsStrategy.h"

using namespace std;

KingBoss::KingBoss(void)
{
	Tetramino *bossTetramino = new Tetramino(kTetraminoBossKing, 3);
	bossTetramino->addObserver(this);
	_bossWithOneTetraminoDelegate = new BossWithOneTetraminoDelegate(bossTetramino);

	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_movementStrategy = new AIMovementStrategy(gameBoard, bossTetramino);
	_spellCastsStrategy = new AISpellCastsStrategy();
}

KingBoss::~KingBoss(void)
{
	delete _bossWithOneTetraminoDelegate;
	delete _movementStrategy;
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