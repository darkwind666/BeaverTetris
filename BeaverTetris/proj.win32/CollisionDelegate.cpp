#include "CollisionDelegate.h"


CollisionDelegate::CollisionDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


CollisionDelegate::~CollisionDelegate(void)
{
}

bool CollisionDelegate::checkCollisionWithDetail(TetraminoDetail aDetail)
{
	GamePositionOnBoard detailPosition = aDetail.getDetailPosition;

	for (int xIndex = detailPosition.xPosition; xIndex <  detailPosition.xPosition + aDetail.getDetailWidth; xIndex++)
	{

		for (int yIndex = detailPosition.yPosition; yIndex < aDetail.getDetailHeight; yIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,yIndex);
			Tetramino tetraminoInDetail = aDetail.getTetraminoForXY(xIndex - detailPosition.xPosition, yIndex - detailPosition.yPosition);

			if (tetraminoInBoard->getTetraminoType > kTetraminoEmpty && tetraminoInDetail.getTetraminoType > kTetraminoEmpty)
			{
				return true;
			}

		}

	}

	return false;
}