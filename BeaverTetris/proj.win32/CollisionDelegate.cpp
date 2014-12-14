#include "CollisionDelegate.h"


CollisionDelegate::CollisionDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


CollisionDelegate::~CollisionDelegate(void)
{
}

bool CollisionDelegate::checkCollisionWithDetail(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition;
	bool collision = collisionWithDetailPositionAndDetail(detailPosition, aDetail);
	return collision;
}

GamePositionOnBoard CollisionDelegate::getCollisionPositionWithBoardForDetail(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition;
	GamePositionOnBoard detailCollisionPosition = detailPosition;

	for (int heightIndex = detailPosition.yPosition; heightIndex <= 0; heightIndex--)
	{
		detailCollisionPosition.yPosition = heightIndex;
		bool collision = collisionWithDetailPositionAndDetail(detailPosition, aDetail);
		if (collision)
		{
			break;
		}
		else
		{
			detailPosition = detailCollisionPosition;
		}
		
	}
	return detailPosition;
}

bool CollisionDelegate::collisionWithDetailPositionAndDetail(GamePositionOnBoard aDetailPosition, TetraminoDetail *aDetail)
{

	bool collision = false;

	for (int xIndex = aDetailPosition.xPosition; xIndex <  aDetailPosition.xPosition + aDetail->getDetailWidth; xIndex++)
	{
	
		for (int yIndex = aDetailPosition.yPosition; yIndex < aDetail->getDetailHeight; yIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,yIndex);
			Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xIndex - aDetailPosition.xPosition, yIndex - aDetailPosition.yPosition);
	
			if (tetraminoInBoard->getTetraminoType > kTetraminoEmpty && tetraminoInDetail->getTetraminoType > kTetraminoEmpty)
			{
				collision = true;
				return collision;
			}
	
		}
	
	}
	return collision;
}