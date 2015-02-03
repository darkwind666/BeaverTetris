#include "TetraminosCombinatorDelegate.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"
#include <stdlib.h>

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
	vector < vector <GamePositionOnBoard> >::iterator tetraminosIterator;
	
	for (tetraminosIterator = aTetraminoDetailsInGame.begin(); tetraminosIterator != aTetraminoDetailsInGame.end(); tetraminosIterator++)
	{
		vector <GamePositionOnBoard> detailElements = *tetraminosIterator;
		TetraminoDetail *detailFromTetraminos = combineTetraminosInDetail(detailElements);
		tetraminosDetails.push_back(detailFromTetraminos);
	}
	return tetraminosDetails;
}

TetraminoDetail* TetraminosCombinatorDelegate::combineTetraminosInDetail(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard maxDetailPosition = getMaxDetailPositionFromDetailsElements(aDetailElements);
	GamePositionOnBoard minDetailPosition = getMinDetailPositionFromDetailsElements(aDetailElements);
	TetraminoDetail *detailFromTetraminos = getDetailWithMaxAndMinPosition(aDetailElements, maxDetailPosition, minDetailPosition);
	return detailFromTetraminos;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getMaxDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard maxDetailPosition = aDetailElements.front();
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		maxDetailPosition.xPosition = max(maxDetailPosition.xPosition, detailElementsIterator->xPosition);
		maxDetailPosition.yPosition = max(maxDetailPosition.yPosition, detailElementsIterator->yPosition);
	}
	return maxDetailPosition;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getMinDetailPositionFromDetailsElements(vector <GamePositionOnBoard> aDetailElements)
{
	GamePositionOnBoard minDetailPosition = aDetailElements.front();
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		minDetailPosition.xPosition = min(minDetailPosition.xPosition, detailElementsIterator->xPosition);
		minDetailPosition.yPosition = min(minDetailPosition.yPosition, detailElementsIterator->yPosition);
	}
	return minDetailPosition;
}

TetraminoDetail* TetraminosCombinatorDelegate::getDetailWithMaxAndMinPosition(vector <GamePositionOnBoard> aDetailElements, GamePositionOnBoard aMaxPosition, GamePositionOnBoard aMinPosition)
{
	GamePositionOnBoard detailSize = getDetailSizeFromMaxAndMinPosition(aMaxPosition, aMinPosition);
	TetraminoDetail *detailFromTetraminos = new TetraminoDetail(detailSize.xPosition, detailSize.yPosition);
	detailFromTetraminos->setDetailPosition(aMinPosition);
	fillDetailWithTetraminos(detailFromTetraminos, aDetailElements);
	return detailFromTetraminos;
}

GamePositionOnBoard TetraminosCombinatorDelegate::getDetailSizeFromMaxAndMinPosition(GamePositionOnBoard aMaxDetailPosition, GamePositionOnBoard aMinDetailPosition)
{
	GamePositionOnBoard detailSize;
	detailSize.xPosition = aMaxDetailPosition.xPosition - aMinDetailPosition.xPosition + 1;
	detailSize.yPosition = aMaxDetailPosition.yPosition - aMinDetailPosition.yPosition + 1;
	return detailSize;
}

void TetraminosCombinatorDelegate::fillDetailWithTetraminos(TetraminoDetail *aDetail, vector <GamePositionOnBoard> aDetailElements)
{
	vector <GamePositionOnBoard>::iterator detailElementsIterator;
	for (detailElementsIterator = aDetailElements.begin(); detailElementsIterator != aDetailElements.end(); detailElementsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *detailElementsIterator;
		Tetramino *tetraminoForDetail = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		GamePositionOnBoard tetraminoPositionInDetail = aDetail->convertAbsolutePositionToPositionInDetail(tetraminoPosition);
		aDetail->setTetraminoForXY(tetraminoForDetail, tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	}
}