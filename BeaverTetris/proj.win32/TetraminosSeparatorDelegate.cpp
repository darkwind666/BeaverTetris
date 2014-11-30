#include "TetraminosSeparatorDelegate.h"

using namespace std;

TetraminosSeparatorDelegate::TetraminosSeparatorDelegate(GameBoard *aGameBoard, ActiveDetails *aActiveDetails)
{
	_gameBoard = aGameBoard;
	_activeDetails = aActiveDetails;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
}


TetraminosSeparatorDelegate::~TetraminosSeparatorDelegate(void)
{

}

void TetraminosSeparatorDelegate::separateTetraminos()
{

	vector < vector <GamePositionOnBoard> > tetraminoDetailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	replaceTetraminosDetailsFromBoardToActiveDetailsStrore(tetraminoDetailsInGame);

}


void TetraminosSeparatorDelegate::replaceTetraminosDetailsFromBoardToActiveDetailsStrore(vector < vector <GamePositionOnBoard> > aTetraminoDetailsInGame)
{

	vector < vector <GamePositionOnBoard> >::iterator tetraminoDetailsInGameIterator;

	for (tetraminoDetailsInGameIterator = aTetraminoDetailsInGame.begin; tetraminoDetailsInGameIterator != aTetraminoDetailsInGame.end; tetraminoDetailsInGameIterator++)
	{
		vector <GamePositionOnBoard> detailElements = *tetraminoDetailsInGameIterator;

		GamePositionOnBoard maxDetailPosition = getMaxDetailPositionFromDetailsElements(detailElements);
		GamePositionOnBoard minDetailPosition = getMinDetailPositionFromDetailsElements(detailElements);
		GamePositionOnBoard detailSize = getDetailSizeFromMaxAndMinPosition(maxDetailPosition, minDetailPosition);

		TetraminoDetail *detailFromTetraminos = getDetailWithMaxMinDetailPositionAndDetailSize(detailElements, maxDetailPosition, minDetailPosition, detailSize);
		_activeDetails->addDetail(detailFromTetraminos);

	}

}

GamePositionOnBoard TetraminosSeparatorDelegate::getMaxDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
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

GamePositionOnBoard TetraminosSeparatorDelegate::getMinDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
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

GamePositionOnBoard TetraminosSeparatorDelegate::getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition)
{
	GamePositionOnBoard detailSize;
	detailSize.xPosition = aMaxDetailPosition.xPosition - aMinDetailPosition.xPosition;
	detailSize.yPosition = aMaxDetailPosition.yPosition - aMinDetailPosition.yPosition;
	return detailSize;
}

TetraminoDetail* TetraminosSeparatorDelegate::getDetailWithMaxMinDetailPositionAndDetailSize(std::vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition, GamePositionOnBoard aDetailSize)
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
		_gameBoard->removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
	
	return detailFromTetraminos;

}