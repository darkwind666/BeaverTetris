#include "TetraminosCombinatorDelegate.h"

using namespace std;


TetraminosCombinatorDelegate::TetraminosCombinatorDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


TetraminosCombinatorDelegate::~TetraminosCombinatorDelegate(void)
{
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
	GamePositionOnBoard maxDetailPosition = aDetailElements.front;

	vector <GamePositionOnBoard>::iterator detailElementsIterator;

	for (detailElementsIterator = aDetailElements.begin; detailElementsIterator != aDetailElements.end; detailElementsIterator++)
	{
		if (maxDetailPosition.xPosition > detailElementsIterator->xPosition && maxDetailPosition.yPosition > detailElementsIterator->yPosition)
		{
			maxDetailPosition = *detailElementsIterator;
		}
	}

	return maxDetailPosition;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getMinDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard minDetailPosition;

	vector <GamePositionOnBoard>::iterator detailElementsIterator;

	for (detailElementsIterator = aDetailElements.begin; detailElementsIterator != aDetailElements.end; detailElementsIterator++)
	{
		if (minDetailPosition.xPosition < detailElementsIterator->xPosition && minDetailPosition.yPosition < detailElementsIterator->yPosition)
		{
			minDetailPosition = *detailElementsIterator;
		}
	}

	return minDetailPosition;

}

GamePositionOnBoard TetraminosCombinatorDelegate::getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition)
{
	GamePositionOnBoard detailSize;
	detailSize.xPosition = aMaxDetailPosition.xPosition - aMinDetailPosition.xPosition;
	detailSize.yPosition = aMaxDetailPosition.yPosition - aMinDetailPosition.yPosition;
	return detailSize;
}

TetraminoDetail* TetraminosCombinatorDelegate::getDetailWithMaxMinDetailPositionAndDetailSize(std::vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition, GamePositionOnBoard aDetailSize)
{
	TetraminoDetail *detailFromTetraminos = new TetraminoDetail(aDetailSize.xPosition, aDetailSize.yPosition);

	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	
	for (detailElementsIterator = aDetailElements.begin; detailElementsIterator != aDetailElements.end; detailElementsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *detailElementsIterator;
		Tetramino *tetraminoForDetail = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		int tetraminoPositionXInDetail = aMinDetailPosition.xPosition - detailElementsIterator->xPosition;
		int tetraminoPositionYInDetail = aMinDetailPosition.yPosition - detailElementsIterator->yPosition;
		detailFromTetraminos->setTetraminoForXY(tetraminoForDetail, tetraminoPositionXInDetail, tetraminoPositionYInDetail);
	}
	
	return detailFromTetraminos;

}