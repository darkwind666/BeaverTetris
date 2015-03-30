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
		if (checkTetraminoForPlacingInBoardRowAndColumn(tetraminoInDetail, aRow, xIndex, aTetraminoDetail))
		{			
			GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();						
			_gameBoard->replaceTetraminoXYposition(tetraminoInDetail, detailPosition.xPosition + xIndex, detailPosition.yPosition + aRow);
		}
		else
		{
			delete tetraminoInDetail;
		}
	}			
}

bool TetraminoDetailLocatorDelegate::checkTetraminoForPlacingInBoardRowAndColumn(Tetramino *aTetramino, int aRow, int aColumn, TetraminoDetail *aTetraminoDetail)
{
	GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();	
	bool tetraminoInBoardEmpty = true;
	GamePositionOnBoard positionInDetail;
	positionInDetail.xPosition = aColumn;
	positionInDetail.yPosition = aRow;
	GamePositionOnBoard absolutePosition = aTetraminoDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
	bool positionInBoard = _gameBoard->positionInBoard(absolutePosition);
	if (positionInBoard)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(absolutePosition.xPosition, absolutePosition.yPosition);
		if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			tetraminoInBoardEmpty = false;
		}
	}
	return (aTetramino->getTetraminoType() > kTetraminoEmpty && positionInBoard == true && tetraminoInBoardEmpty == true);
}