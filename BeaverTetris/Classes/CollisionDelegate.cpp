#include "CollisionDelegate.h"
#include "TetraminoDetail.h"
#include "GameBoard.h"

CollisionDelegate::CollisionDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


CollisionDelegate::~CollisionDelegate(void)
{
}

bool CollisionDelegate::checkCollisionWithDetail(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	bool collision = collisionWithDetailPositionAndDetail(detailPosition, aDetail);
	return collision;
}

GamePositionOnBoard CollisionDelegate::getCollisionPositionWithBoardForDetail(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
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

	for (int xIndex = aDetailPosition.xPosition; xIndex <  aDetailPosition.xPosition + aDetail->getDetailWidth(); xIndex++)
	{
	
		for (int yIndex = aDetailPosition.yPosition; yIndex < aDetail->getDetailHeight(); yIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,yIndex);
			Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xIndex - aDetailPosition.xPosition, yIndex - aDetailPosition.yPosition);
	
			if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty && tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
			{
				collision = true;
				return collision;
			}
	
		}
	
	}
	return collision;
}

bool CollisionDelegate::checkCollisionDetailWithGameBorders(TetraminoDetail *detailWithNewPosition)
{
	bool collision = false;
	if (detailOutBoard(detailWithNewPosition))
	{
		int detailWidth = detailWithNewPosition->getDetailWidth();
		for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
		{
			if (checkCollisionWithDetailRow(widthIndex, detailWithNewPosition))
			{
				collision = true;
				break;
			}
		}
	}
	return collision;
}

bool CollisionDelegate::detailOutBoard(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	
	int detailWidth = aDetail->getDetailWidth();
	int detailHeight = aDetail->getDetailHeight();
	
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	
	bool outBoardHeigh = (detailPosition.yPosition < 0);
	bool outBoardWidth = (detailPosition.xPosition < 0 || detailPosition.xPosition > (gameBoardWidth - detailWidth));
	return (outBoardHeigh == true ||  outBoardWidth == true);
}

bool CollisionDelegate::checkCollisionWithDetailRow(int detailRow ,TetraminoDetail *aDetail)
{
	bool collision = false;
	int detailHeight = aDetail->getDetailHeight();
	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{
		GamePositionOnBoard positionInDetail;
		positionInDetail.xPosition = detailRow;
		positionInDetail.yPosition = heightIndex;
		if (collisionWithPositionInDetail(positionInDetail, aDetail))
		{
			collision = true;
			break;
		}
	}
	return collision;
}

bool CollisionDelegate::collisionWithPositionInDetail(GamePositionOnBoard aPosition, TetraminoDetail *aDetail)
{
	bool collision = false;
	GamePositionOnBoard absolutePosition = aDetail->convertPositionInDetailToAbsolutePosition(aPosition);
	if (tetraminoInDetailOutBoard(absolutePosition, aDetail))
	{
		Tetramino *detailTetramino = aDetail->getTetraminoForXY(aPosition.xPosition, aPosition.yPosition);
		if (detailTetramino->getTetraminoType() > kTetraminoEmpty)
		{
			collision = true;
		}
	
	}
	return collision;
}

bool CollisionDelegate::tetraminoInDetailOutBoard(GamePositionOnBoard aTetraminoAbsolutePosition, TetraminoDetail *aDetail)
{
	bool collisionWithDownBorder = (aTetraminoAbsolutePosition.yPosition < 0);
	bool collisionWithLeftBorder = (aTetraminoAbsolutePosition.xPosition < 0); 
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	int detailWidth = aDetail->getDetailWidth();
	bool collisionWithRightBorder = (aTetraminoAbsolutePosition.xPosition > (gameBoardWidth - detailWidth));
	return (collisionWithDownBorder == true || collisionWithLeftBorder == true || collisionWithRightBorder == true);
}