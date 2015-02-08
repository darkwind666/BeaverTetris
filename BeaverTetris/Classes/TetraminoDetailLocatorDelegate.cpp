#include "TetraminoDetailLocatorDelegate.h"
#include "Tetramino.h"
#include "GameBoard.h"
#include "TetraminoDetail.h"

TetraminoDetailLocatorDelegate::TetraminoDetailLocatorDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


TetraminoDetailLocatorDelegate::~TetraminoDetailLocatorDelegate(void)
{
}

void TetraminoDetailLocatorDelegate::writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail)
{
	for (int yIndex = 0; yIndex < aTetraminoDetail->getDetailHeight(); yIndex++)
	{
		writeTetraminoRowFromDetail(yIndex, aTetraminoDetail);
	}	
}

void TetraminoDetailLocatorDelegate::writeTetraminoRowFromDetail(int aRow, TetraminoDetail *aTetraminoDetail)
{
	for (int xIndex = 0; xIndex < aTetraminoDetail->getDetailWidth(); xIndex++)
	{			
		Tetramino *tetraminoInDetail = aTetraminoDetail->getTetraminoForXY(xIndex,aRow);
		if (checkTetraminoForPlacingInBoardRow(tetraminoInDetail, aRow, aTetraminoDetail))
		{			
			GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();						
			_gameBoard->replaceTetraminoXYposition(tetraminoInDetail ,detailPosition.xPosition + xIndex, detailPosition.yPosition + aRow);
		}
		else
		{
			delete tetraminoInDetail;
		}
	}			
}

bool TetraminoDetailLocatorDelegate::checkTetraminoForPlacingInBoardRow(Tetramino *aTetramino, int aRow, TetraminoDetail *aTetraminoDetail)
{
	GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();	
	bool tetraminoInBoard = (detailPosition.yPosition + aRow) < _gameBoard->getGameBoardHeight();
	return (aTetramino->getTetraminoType() > kTetraminoEmpty && tetraminoInBoard == true);
}