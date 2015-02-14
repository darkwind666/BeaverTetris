#include "PrincessBoss.h"
#include "Tetramino.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "KeysForEnumsDataSource.h"
#include "AIMovementStrategy.h"

using namespace std;

PrincessBoss::PrincessBoss(GameLevelInformation aLevelInformation)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_princessBosses = makePrincessWithLevelData(aLevelInformation);

	KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_bossKey = keysForEnumsDataSource->getKeyForTetraminoType(kTetraminoBossPrincess);
}


PrincessBoss::~PrincessBoss(void)
{
}

vector<PrincessBossInformation> PrincessBoss::makePrincessWithLevelData(GameLevelInformation aLevelInformation)
{
	vector<PrincessBossInformation> bosses;
	int bossCount = aLevelInformation.availableBosses.bossesCount;
	for (int bossIndex = 0; bossIndex < bossCount; bossIndex++)
	{
		PrincessBossInformation princess;
		princess.bossTetramino = makeBossTetraminoWithIndexAndBossCount(bossIndex, bossCount);
		princess.bossMovementStrategy = makeBossMovementWithTetramino(princess.bossTetramino);
		bosses.push_back(princess);
	}
	return bosses;
}

Tetramino* PrincessBoss::makeBossTetraminoWithIndexAndBossCount(int aBossIndex, int aBossCount)
{
	Tetramino* boss = new Tetramino(kTetraminoBossPrincess, 2);
	boss->addObserver(this);

	int xOffset = tetrisBlocksWidth / (aBossCount + 1);
	int xPosition = (xOffset * (aBossIndex + 1));
	int yPosition = standartDetailHeight/2;
	_gameBoard->replaceTetraminoXYposition(boss, xPosition, yPosition);
	return boss;
}

AIMovementStrategy* PrincessBoss::makeBossMovementWithTetramino(Tetramino *aTetramino)
{
	AIMovementStrategy *bossMovement = new AIMovementStrategy(_gameBoard, aTetramino);
	return bossMovement;
}

int PrincessBoss::getVictoryStateInformationCount(void)
{
	return _princessBosses.size();
}

int PrincessBoss::getVictoryStateInformationForIndex(int aIndex)
{
	int liveCount = 0;
	if (_princessBosses.size() > 0)
	{
		PrincessBossInformation princess = _princessBosses[aIndex];
		liveCount = princess.bossTetramino->getTetraminoLivesCount();
	}
	return liveCount;
}

string PrincessBoss::getVictoryStateIconImageForIndex(int aIndex)
{
	return _bossKey;
}

bool PrincessBoss::playerWin(void)
{
	bool win = true;
	if (_princessBosses.size() > 0)
	{
		win = false;
	}
	return win;
}

void PrincessBoss::update(void)
{
	srand(time(0));
	vector<PrincessBossInformation>::iterator bossIterator;
	for (bossIterator = _princessBosses.begin(); bossIterator != _princessBosses.end(); bossIterator++)
	{
		PrincessBossInformation princess = *bossIterator;
		princess.bossMovementStrategy->updateAI();
	}
}


void PrincessBoss::tetraminoRemoving(Tetramino *aTetramino)
{
	int tetraminoIndex = getTetraminoIndex(aTetramino);
	PrincessBossInformation princess = _princessBosses[tetraminoIndex];
	delete princess.bossMovementStrategy;
	_princessBosses.erase(_princessBosses.begin() + tetraminoIndex);
}

int PrincessBoss::getTetraminoIndex(Tetramino *aTetramino)
{
	int tetraminoIndex = 0;
	vector<PrincessBossInformation>::iterator bossIterator;
	for (bossIterator = _princessBosses.begin(); bossIterator != _princessBosses.end(); bossIterator++)
	{
		PrincessBossInformation princess = *bossIterator;
		if (princess.bossTetramino == aTetramino)
		{
			tetraminoIndex = distance(_princessBosses.begin(), bossIterator);
			break;
		}
	}
	return tetraminoIndex;
}

