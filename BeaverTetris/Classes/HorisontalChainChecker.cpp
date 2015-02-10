#include "HorisontalChainChecker.h"
#include "TetraminosChainCleaner.h"
#include "GameBoard.h"
#include "TetraminoDetail.h"
#include "TetraminosCombinatorDelegate.h"
#include "GameDesignConstants.h"
#include "ChainFromTetraminosChecker.h"

using namespace std;

HorisontalChainChecker::HorisontalChainChecker(TetraminosChainCleaner *aTetraminosChainCleaner, GameBoard *aGameBoard)
{
	_tetraminosChainCleaner = aTetraminosChainCleaner;
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_chainFromTetraminosChecker = new ChainFromTetraminosChecker();
}


HorisontalChainChecker::~HorisontalChainChecker(void)
{
	delete _tetraminosCombinatorDelegate;
	delete _chainFromTetraminosChecker;
}

void HorisontalChainChecker::checkChainInDetailHorisontals(vector<GamePositionOnBoard> aTetraminos)
{
	TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(aTetraminos);
	for (int yIndex = 0; yIndex < detailFromElements->getDetailHeight(); yIndex++)
	{
		vector<GamePositionOnBoard> chainElements = getChainInDetailHorisontal(detailFromElements, yIndex);
		if (chainElements.size() >= tetraminosInChainCount)
		{
			_tetraminosChainCleaner->cleanChain(chainElements);
		}
	}
	delete detailFromElements;
}

vector<GamePositionOnBoard> HorisontalChainChecker::getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition)
{
	vector<GamePositionOnBoard> tetraminosPositions;
	for (int xIndex = 0; xIndex < aDetail->getDetailWidth(); xIndex++)
	{
		GamePositionOnBoard positionInDetail;
		positionInDetail.xPosition = xIndex;
		positionInDetail.yPosition = yPosition;
		tetraminosPositions.push_back(positionInDetail);
	}
	vector<GamePositionOnBoard> chain = _chainFromTetraminosChecker->getChainFromTetraminosPositions(tetraminosPositions, aDetail);
	return chain;
}

