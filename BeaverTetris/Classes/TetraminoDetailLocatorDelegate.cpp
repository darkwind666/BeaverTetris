#include "TetraminoDetailLocatorDelegate.h"
#include "Tetramino.h"

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
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
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