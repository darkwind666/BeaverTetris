#include "BossEnvironmentFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "GameDesignConstants.h"
#include "Tetramino.h"
#include "TetraminosFactory.h"

using namespace std;

const int bossEnvironmentLinesCount = 3;

BossEnvironmentFactory::BossEnvironmentFactory(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
}


BossEnvironmentFactory::~BossEnvironmentFactory(void)
{
}

void BossEnvironmentFactory::makeBossEnvironment()
{
	vector< vector<int> > tetraminoElements = getBoardTetraminosTemplate();
	fillBoardWithTetraminos(tetraminoElements);
}

vector< vector<int> > BossEnvironmentFactory::getBoardTetraminosTemplate()
{
	int tetraminoElementsInBoard[standartDetailHeight][tetrisBlocksWidth] = {
		{0,0,2,2,1,1,1,3,3,3},
		{1,1,2,2,3,0,4,4,1,1},
		{0,1,1,3,3,3,4,4,1,1},
	};
	vector< vector<int> > tetraminoElements = convertMasiveToVector(&tetraminoElementsInBoard[0][0]);
	return tetraminoElements;
}

vector< vector<int> > BossEnvironmentFactory::convertMasiveToVector(int *aSourceMassive)
{
	vector< vector<int> > tetraminoElements;
	for (int yIndex = 0; yIndex < standartDetailHeight; yIndex++)
	{
		vector<int> tetraminoElementsLine = getTetraminosElementsLineFromSource(yIndex, aSourceMassive);
		tetraminoElements.push_back(tetraminoElementsLine);
	}
	return tetraminoElements;
}

vector<int> BossEnvironmentFactory::getTetraminosElementsLineFromSource(int yIndex, int *aSourceMassive)
{
	vector<int> tetraminoElementsLine;
	for (int xIndex = 0; xIndex < tetrisBlocksWidth; xIndex++)
	{
		int tetraminoTag = aSourceMassive[yIndex * tetrisBlocksWidth + xIndex];
		tetraminoElementsLine.push_back(tetraminoTag);
	}
	return tetraminoElementsLine;
}

void BossEnvironmentFactory::fillBoardWithTetraminos(vector< vector<int> > aTetraminoElements)
{
	vector< vector<int> >::iterator linesIterator;
	for (linesIterator = aTetraminoElements.begin(); linesIterator != aTetraminoElements.end(); linesIterator++)
	{
		int lineIndex = distance(aTetraminoElements.begin(), linesIterator);
		vector<int> tetraminosRow = *linesIterator;
		fillBoardLineWithTetraminos(lineIndex, tetraminosRow);
	}
}

void BossEnvironmentFactory::fillBoardLineWithTetraminos(int aLineIndex, vector<int> aTetraminoElements)
{
	vector<int>::iterator rowIterator;
	for (rowIterator = aTetraminoElements.begin(); rowIterator != aTetraminoElements.end(); rowIterator++)
	{
		int rowIndex = distance(aTetraminoElements.begin(), rowIterator);
		int tetraminoTypeTag = *rowIterator;
		TetraminoType type = (TetraminoType)tetraminoTypeTag;
		Tetramino *tetraminoFromTemplate = _tetraminosFactory->getNewTetraminoWithType(type);
		_gameBoard->replaceTetraminoXYposition(tetraminoFromTemplate, rowIndex, (standartDetailHeight - aLineIndex - 1));
	}
}
