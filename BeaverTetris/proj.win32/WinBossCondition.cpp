#include "WinBossCondition.h"
#include "GameBoard.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewSuffixes.h"

using namespace std;

WinBossCondition::WinBossCondition(GameLevelInformation aLevelInformation)
{
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
	_bosses = getBossesFromLevel(aLevelInformation);
	subscribeToBosses();
}


WinBossCondition::~WinBossCondition(void)
{
}

int WinBossCondition::getVictoryStateInformationCount(void)
{
	return _bosses.size();
}

int WinBossCondition::getVictoryStateInformationForIndex(int aIndex)
{
	Tetramino *boss = _bosses[aIndex];
	return boss->getTetraminoLivesCount();
}

string WinBossCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	Tetramino *boss = _bosses[aIndex];
	string tetraminosTypeForWinName = _keysForEnumsDataSource->getKeyForTetraminoType(boss->getTetraminoType());
	return (tetraminosTypeForWinName + tetraminoForWinConditionIconSuffixKey);
}

bool WinBossCondition::playerWin(void)
{
	bool playerWin = true;

	vector<Tetramino*>::iterator bossesIterator;
	
	for (bossesIterator = _bosses.begin(); bossesIterator != _bosses.end(); bossesIterator++)
	{
		Tetramino *bossTetramino = *bossesIterator;
		if (bossTetramino->getTetraminoLivesCount() >= 0)
		{
			playerWin = false;
			return playerWin;
		}
	}
	return playerWin;
}

void WinBossCondition::tetraminoRemoving(Tetramino *aTetramino)
{
	vector<Tetramino*>::iterator removingElementIndex = find(_bosses.begin(), _bosses.end(), aTetramino);
	aTetramino->removeObserver(this);
	_bosses.erase(removingElementIndex);
}

void WinBossCondition::update(void)
{

}

vector<Tetramino*> WinBossCondition::getBossesFromLevel(GameLevelInformation aLevelInformation)
{
	vector<Tetramino*> bosses; 

	GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	vector<GamePositionOnBoard> gameBossesPositions = gameBoard->getTetraminosForType(aLevelInformation.availableBosses.aBossType);

	vector<GamePositionOnBoard>::iterator bossesPositionsIterator;

	for (bossesPositionsIterator = gameBossesPositions.begin(); bossesPositionsIterator != gameBossesPositions.end(); bossesPositionsIterator++)
	{
		GamePositionOnBoard bossPosition = *bossesPositionsIterator;
		Tetramino *bossTetramino = gameBoard->getTetraminoForXYposition(bossPosition.xPosition, bossPosition.yPosition);
		bosses.push_back(bossTetramino);
	}
	return bosses;
}

void WinBossCondition::subscribeToBosses()
{
	vector<Tetramino*>::iterator bossesIterator;

	for (bossesIterator = _bosses.begin(); bossesIterator != _bosses.end(); bossesIterator++)
	{
		Tetramino *bossTetramino = *bossesIterator;
		bossTetramino->addObserver(this);
	}

}