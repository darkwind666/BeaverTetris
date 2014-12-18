#include "RemoveSomeTetraminosCondition.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewSuffixes.h"

using namespace std;

RemoveSomeTetraminosCondition::RemoveSomeTetraminosCondition(GameLevelInformation aLevelInformation)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_gameBoard->addObserver(this);
	_tetraminosCollectionForWin = aLevelInformation.tetraminosCollectionForWin;
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}


RemoveSomeTetraminosCondition::~RemoveSomeTetraminosCondition(void)
{
	_gameBoard->removeObserver(this);
}

int RemoveSomeTetraminosCondition::getVictoryStateInformationCount(void)
{
	return _tetraminosCollectionForWin.size();
}

int RemoveSomeTetraminosCondition::getVictoryStateInformationForIndex(int aIndex)
{
	TetraminosForWinInformation tetraminosForWin = _tetraminosCollectionForWin[aIndex];
	return tetraminosForWin.tetraminosCount;
}

string RemoveSomeTetraminosCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	TetraminosForWinInformation tetraminosForWin = _tetraminosCollectionForWin[aIndex];
	string tetraminosTypeForWinName = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminosForWin.tetraminoType);
	return (tetraminosTypeForWinName + tetraminoForWinConditionIconSuffixKey);
}

bool RemoveSomeTetraminosCondition::playerWin(void)
{
	bool playerWin = true;

	vector<TetraminosForWinInformation>::iterator tetraminosIterator;
	for (tetraminosIterator = _tetraminosCollectionForWin.begin(); tetraminosIterator != _tetraminosCollectionForWin.end(); tetraminosIterator++)
	{
		TetraminosForWinInformation tetraminosForWin = *tetraminosIterator;
		if (tetraminosForWin.tetraminosCount > 0)
		{
			playerWin = false;
			break;
		}
	}
	return playerWin;
}

void RemoveSomeTetraminosCondition::tetraminoRemoving(Tetramino *aTetramino)
{
	vector<TetraminosForWinInformation>::iterator tetraminosIterator;
	for (tetraminosIterator = _tetraminosCollectionForWin.begin(); tetraminosIterator != _tetraminosCollectionForWin.end(); tetraminosIterator++)
	{
		TetraminosForWinInformation tetraminosForWin = *tetraminosIterator;
		if (tetraminosForWin.tetraminoType == aTetramino->getTetraminoType())
		{
			tetraminosForWin.tetraminosCount = tetraminosForWin.tetraminosCount - 1;
			break;
		}
	}
}

void RemoveSomeTetraminosCondition::update(void)
{

}




