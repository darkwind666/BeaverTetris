#include "BossEnvironmentFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "Tetramino.h"
#include "GameHelper.h"

using namespace std;

const int bossEnvironmentLinesCount = 3;

BossEnvironmentFactory::BossEnvironmentFactory(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}


BossEnvironmentFactory::~BossEnvironmentFactory(void)
{
}

void BossEnvironmentFactory::makeBossEnvironment()
{
	srand(time(0));
	for (int lineIndex = 0; lineIndex < bossEnvironmentLinesCount; lineIndex++)
	{
		makeLineForIndex(lineIndex);
	}
}

void BossEnvironmentFactory::makeLineForIndex(int aLineIndex)
{
	vector<TetraminoType> tetraminosInLine = getTetraminoTypesInLine(aLineIndex);
	cleanFullLineInTetraminosTypes(tetraminosInLine);
	cleanTetraminosChainsInTetraminosTypes(tetraminosInLine);
	writeTetraminosInBoardLine(tetraminosInLine, aLineIndex);
}

vector<TetraminoType> BossEnvironmentFactory::getTetraminoTypesInLine(int aLineIndex)
{
	vector<TetraminoType> tetraminosInLine;
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		TetraminoType type = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
		tetraminosInLine.push_back(type);
	}
	return tetraminosInLine;
}

void BossEnvironmentFactory::cleanFullLineInTetraminosTypes(vector<TetraminoType> &aTetraminosInLine)
{
	vector<TetraminoType>::iterator emptyTetramino;
	emptyTetramino = find(aTetraminosInLine.begin(), aTetraminosInLine.end(), kTetraminoEmpty);
	if (emptyTetramino == aTetraminosInLine.end())
	{
		int randomTetraminoIndex = GameHelper::getRandomNumberFromUpInterval(aTetraminosInLine.size());
		aTetraminosInLine[randomTetraminoIndex] = kTetraminoEmpty;
	}
}

void BossEnvironmentFactory::cleanTetraminosChainsInTetraminosTypes(vector<TetraminoType> &aTetraminosInLine)
{
	vector<TetraminoType> chain;

	vector<TetraminoType>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminosInLine.begin(); tetraminosIterator != aTetraminosInLine.end(); tetraminosIterator++)
	{
		TetraminoType type = *tetraminosIterator;
		
		if (chain.size() == 0)
		{
			if (type != kTetraminoEmpty)
			{
				chain.push_back(type);
			}
			continue;
		}

		if (type == chain[0])
		{
			chain.push_back(type);
			if (chain.size() >= tetraminosInChainCount)
			{
				int index = distance(aTetraminosInLine.begin(), tetraminosIterator);
				TetraminoType type = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
				while (type != chain[0]  && type != kTetraminoEmpty)
				{
					type = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
				}
				aTetraminosInLine[(index - 1)] = type;
			}
		}
		else
		{
			chain.clear();
			chain.push_back(type);
		}
	}
}

void BossEnvironmentFactory::writeTetraminosInBoardLine(vector<TetraminoType> aTetraminosInLine, int aLineIndex)
{
	vector<TetraminoType>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminosInLine.begin(); tetraminosIterator != aTetraminosInLine.end(); tetraminosIterator++)
	{
		TetraminoType type = *tetraminosIterator;
		Tetramino *newTetramino = new Tetramino(type);
		int widthIndex = distance(aTetraminosInLine.begin(), tetraminosIterator);
		_gameBoard->replaceTetraminoXYposition(newTetramino, widthIndex, aLineIndex);
	}
}