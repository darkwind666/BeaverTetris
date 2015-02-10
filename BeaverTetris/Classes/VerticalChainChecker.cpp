#include "VerticalChainChecker.h"
#include "TetraminosChainCleaner.h"
#include "GameBoard.h"
#include "TetraminoDetail.h"
#include "TetraminosCombinatorDelegate.h"
#include "GameDesignConstants.h"
#include "ChainFromTetraminosChecker.h"

using namespace std;

VerticalChainChecker::VerticalChainChecker(TetraminosChainCleaner *aTetraminosChainCleaner, GameBoard *aGameBoard)
{
	_tetraminosChainCleaner = aTetraminosChainCleaner;
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_chainFromTetraminosChecker = new ChainFromTetraminosChecker();
}


VerticalChainChecker::~VerticalChainChecker(void)
{
	delete _tetraminosCombinatorDelegate;
	delete _chainFromTetraminosChecker;
}

void VerticalChainChecker::checkChainInDetailVerticals(vector<GamePositionOnBoard> aTetraminos)
{
	TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(aTetraminos);
	for (int xIndex = 0; xIndex < detailFromElements->getDetailWidth(); xIndex++)
	{
		vector<GamePositionOnBoard> chainElements = getChainInDetailVertical(detailFromElements, xIndex);
		if (chainElements.size() >= tetraminosInChainCount)
		{
			_tetraminosChainCleaner->cleanChain(chainElements);
		}
	}
	delete detailFromElements;
}

vector<GamePositionOnBoard> VerticalChainChecker::getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition)
{
	vector<GamePositionOnBoard> tetraminosPositions;
	for (int yIndex = 0; yIndex < aDetail->getDetailHeight(); yIndex++)
	{
		GamePositionOnBoard positionInDetail;
		positionInDetail.xPosition = xPosition;
		positionInDetail.yPosition = yIndex;
		tetraminosPositions.push_back(positionInDetail);
	}
	vector<GamePositionOnBoard> chain = _chainFromTetraminosChecker->getChainFromTetraminosPositions(tetraminosPositions, aDetail);
	return chain;
}
