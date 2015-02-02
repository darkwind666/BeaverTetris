#include "TetraminosCombinatorDelegate.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"

using namespace std;


TetraminosCombinatorDelegate::TetraminosCombinatorDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


TetraminosCombinatorDelegate::~TetraminosCombinatorDelegate(void)
{
}

vector <TetraminoDetail*> TetraminosCombinatorDelegate::combineTetraminosInDetails(vector < vector <GamePositionOnBoard> > aTetraminoDetailsInGame)
{
	vector <TetraminoDetail*> tetraminosDetails;

	vector < vector <GamePositionOnBoard> >::iterator tetraminoDetailsInGameIterator;
	
	for (tetraminoDetailsInGameIterator = aTetraminoDetailsInGame.begin(); tetraminoDetailsInGameIterator != aTetraminoDetailsInGame.end(); tetraminoDetailsInGameIterator++)
	{
		vector <GamePositionOnBoard> detailElements = *tetraminoDetailsInGameIterator;
		TetraminoDetail *detailFromTetraminos = combineTetraminosInDetail(detailElements);
		tetraminosDetails.push_back(detailFromTetraminos);
	}
	return tetraminosDetails;
}

TetraminoDetail* TetraminosCombinatorDelegate::combineTetraminosInDetail(vector <GamePositionOnBoard> aDetailElements)
{
	
	GamePositionOnBoard maxDetailPosition = getMaxDetailPositionFromDetailsElements(aDetailElements);
	GamePositionOnBoard minDetailPosition = getMinDetailPositionFromDetailsElements(aDetailElements);
	GamePositionOnBoard detailSize = getDetailSizeFromMaxAndMinPosition(maxDetailPosition, minDetailPosition);
	
	TetraminoDetail *detailFromTetraminos = getDetailWithMaxMinDetailPositionAndDetailSize(aDetailElements, maxDetailPosition, minDetailPosition, detailSize);
	return detailFromTetraminos;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getMaxDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard maxDetailPosition = aDetailElements.front();

	vector <GamePositionOnBoard>::iterator detailElementsIterator;

	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		if (detailElementsIterator->xPosition > maxDetailPosition.xPosition)
		{
			maxDetailPosition.xPosition = detailElementsIterator->xPosition;
		}

		if (detailElementsIterator->yPosition > maxDetailPosition.yPosition)
		{
			maxDetailPosition.yPosition = detailElementsIterator->yPosition;
		}

	}

	return maxDetailPosition;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getMinDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard minDetailPosition = aDetailElements.front();

	vector <GamePositionOnBoard>::iterator detailElementsIterator;

	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{

		if (detailElementsIterator->xPosition < minDetailPosition.xPosition)
		{
			minDetailPosition.xPosition = detailElementsIterator->xPosition;
		}

		if (detailElementsIterator->yPosition < minDetailPosition.yPosition)
		{
			minDetailPosition.yPosition = detailElementsIterator->yPosition;
		}

	}

	return minDetailPosition;

}

GamePositionOnBoard TetraminosCombinatorDelegate::getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition)
{
	GamePositionOnBoard detailSize;
	detailSize.xPosition = aMaxDetailPosition.xPosition - aMinDetailPosition.xPosition + 1;
	detailSize.yPosition = aMaxDetailPosition.yPosition - aMinDetailPosition.yPosition + 1;
	return detailSize;
}

TetraminoDetail* TetraminosCombinatorDelegate::getDetailWithMaxMinDetailPositionAndDetailSize(std::vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition, GamePositionOnBoard aDetailSize)
{
	TetraminoDetail *detailFromTetraminos = new TetraminoDetail(aDetailSize.xPosition, aDetailSize.yPosition);
	detailFromTetraminos->setDetailPosition(aMinDetailPosition);

	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	
	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *detailElementsIterator;
		Tetramino *tetraminoForDetail = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		GamePositionOnBoard tetraminoPositionInDetail = detailFromTetraminos->convertAbsolutePositionToPositionInDetail(tetraminoPosition);
		detailFromTetraminos->setTetraminoForXY(tetraminoForDetail, tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	}
	
	return detailFromTetraminos;

}