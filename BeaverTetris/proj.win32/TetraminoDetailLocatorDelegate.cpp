#include "TetraminoDetailLocatorDelegate.h"


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
			
		for (int xIndex = 0; xIndex < aTetraminoDetail->getDetailWidth(); xIndex++)
		{			
			Tetramino *tetraminoInDetail = aTetraminoDetail->getTetraminoForXY(xIndex,yIndex);			
			
			if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
			{			
				GamePositionOnBoard detailPosition = aTetraminoDetail->getDetailPosition();						
				_gameBoard->setTetraminoXYposition(tetraminoInDetail ,detailPosition.xPosition + xIndex, detailPosition.yPosition + yIndex);
			}			
			
		}			
			
	}	
}