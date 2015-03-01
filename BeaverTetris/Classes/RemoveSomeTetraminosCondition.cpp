#include "RemoveSomeTetraminosCondition.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewSuffixes.h"
#include "GameBoard.h"
#include "KeysForEnumsDataSource.h"
#include "RocketSpell.h"
#include "Tetramino.h"

using namespace std;

RemoveSomeTetraminosCondition::RemoveSomeTetraminosCondition(GameLevelInformation aLevelInformation)
{
	 GameBoard *gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	 gameBoard->addObserver(this);

	 RocketSpell *rocketSpellModel = (RocketSpell*)ServiceLocator::getServiceForKey(rocketSpellModelKey);
	 rocketSpellModel->addObserver(this);

	_tetraminosCollectionForWin = aLevelInformation.tetraminosCollectionForWin;
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}


RemoveSomeTetraminosCondition::~RemoveSomeTetraminosCondition(void)
{
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
		TetraminosForWinInformation &tetraminosForWin = *tetraminosIterator;
		if (tetraminosForWin.tetraminoType == aTetramino->getTetraminoType())
		{
			tetraminosForWin.tetraminosCount = tetraminosForWin.tetraminosCount - 1;
			break;
		}
	}
	removeFilledCollections();
}

void RemoveSomeTetraminosCondition::removeFilledCollections()
{
	vector<int> indexesToRemove = getIndexesToRemove();
	removeCollectionsForIndexes(indexesToRemove);
}

vector<int> RemoveSomeTetraminosCondition::getIndexesToRemove()
{
	vector<int> indexesToRemove;
	vector<TetraminosForWinInformation>::iterator tetraminosIterator;
	for (tetraminosIterator = _tetraminosCollectionForWin.begin(); tetraminosIterator != _tetraminosCollectionForWin.end(); tetraminosIterator++)
	{
		TetraminosForWinInformation tetraminosForWin = *tetraminosIterator;
		if (tetraminosForWin.tetraminosCount <= 0)
		{
			int index = distance(_tetraminosCollectionForWin.begin(), tetraminosIterator);
			indexesToRemove.push_back(index);
		}
	}
	return indexesToRemove;
}

void RemoveSomeTetraminosCondition::removeCollectionsForIndexes(vector<int> aIndexes)
{
	vector<int>::iterator idexesIterator;
	for (idexesIterator = aIndexes.begin(); idexesIterator != aIndexes.end(); idexesIterator++)
	{
		int index = *idexesIterator;
		_tetraminosCollectionForWin.erase(_tetraminosCollectionForWin.begin() + index);
	}
}

void RemoveSomeTetraminosCondition::update(void)
{

}




