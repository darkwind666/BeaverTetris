#include "QueenBoss.h"
#include "Tetramino.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "KeysForEnumsDataSource.h"

using namespace std;

QueenBoss::QueenBoss(void)
{
	_bossTetramino = new Tetramino(kTetraminoBossQueen, 3);
	_bossTetramino->addObserver(this);

	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	gameBoard->replaceTetraminoXYposition(_bossTetramino,((tetrisBlocksWidth / 2) - 1), (standartDetailHeight/2));

	KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_bossKey = keysForEnumsDataSource->getKeyForTetraminoType(kTetraminoBossQueen);
}


QueenBoss::~QueenBoss(void)
{
}

int QueenBoss::getVictoryStateInformationCount(void)
{
	return 1;
}

int QueenBoss::getVictoryStateInformationForIndex(int aIndex)
{
	int stateInformation = 0;
	if (_bossTetramino != NULL)
	{
		stateInformation = getBossStateInformation();
	}
	return stateInformation;
}

int QueenBoss::getBossStateInformation()
{
	int bossStateInformation = _bossTetramino->getTetraminoLivesCount();
	if (bossStateInformation < 0)
	{
		bossStateInformation = 0;
	}
	return bossStateInformation;
}

string QueenBoss::getVictoryStateIconImageForIndex(int aIndex)
{
	return _bossKey;
}

bool QueenBoss::playerWin(void)
{
	bool win = true;
	if (_bossTetramino != NULL)
	{
		win = getBossWin();
	}
	return win;
}

bool QueenBoss::getBossWin()
{
	bool winBoss = true;
	if (_bossTetramino->getTetraminoLivesCount() > 0)
	{
		winBoss = false;
	}
	return winBoss;
}

void QueenBoss::update(void)
{
	
}

void QueenBoss::tetraminoRemoving(Tetramino *aTetramino)
{
	_bossTetramino = NULL;
}