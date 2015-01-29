#include "CollisionDelegate.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "GameBoard.h"

CollisionDelegate::CollisionDelegate(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
}


CollisionDelegate::~CollisionDelegate(void)
{
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
	bool collisionWithRightBorder = (aTetraminoAbsolutePosition.xPosition > (gameBoardWidth - 1));
	return (collisionWithDownBorder == true || collisionWithLeftBorder == true || collisionWithRightBorder == true);
}




bool CollisionDelegate::checkCollisionDetailWithOtherTetraminos(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	bool collision = false;
	for (int xIndex = detailPosition.xPosition; xIndex <  detailPosition.xPosition + aDetail->getDetailWidth(); xIndex++)
	{
		if (checkCollisionColumnWithOtherTetraminos(xIndex, aDetail))
		{
			collision = true;
			break;
		}
	}
	return collision;
}

bool CollisionDelegate::checkCollisionColumnWithOtherTetraminos(int aColumn, TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	bool collision = false;
	for (int yIndex = detailPosition.yPosition; yIndex < detailPosition.yPosition + aDetail->getDetailHeight(); yIndex++)
	{
		GamePositionOnBoard gameBoardPosition;
		gameBoardPosition.xPosition = aColumn;
		gameBoardPosition.yPosition = yIndex;
		if (checkCollisionDetailWithOtherTetraminosOnPosition(aDetail, gameBoardPosition))
		{
			collision = true;
			break;
		}
	}
	return collision;
}

bool CollisionDelegate::checkCollisionDetailWithOtherTetraminosOnPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition)
{
	bool collision = false;
	if (positionInBoard(aPosition))
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		GamePositionOnBoard positionInTetramino = aDetail->convertAbsolutePositionToPositionInDetail(aPosition);
		Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(positionInTetramino.xPosition, positionInTetramino.yPosition);
		if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty && tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			collision = true;
		}
	}
	return collision;
}

bool CollisionDelegate::positionInBoard(GamePositionOnBoard aPosition)
{
	bool inWidthInterval = (aPosition.xPosition >= 0 && aPosition.xPosition < _gameBoard->getGameBoardWidth());
	bool inHeightInterval = (aPosition.yPosition >= 0 && aPosition.yPosition < _gameBoard->getGameBoardHeight());
	return (inWidthInterval == true && inHeightInterval == true);
}

GamePositionOnBoard CollisionDelegate::getCollisionPositionWithBoardForDetail(TetraminoDetail *aDetail)
{
	GamePositionOnBoard detailPosition = aDetail->getDetailPosition();
	TetraminoDetail *detailWithNewPosition = new TetraminoDetail(*aDetail);

	int tetraminoHeight = aDetail->getDetailHeight();
	for (int heightIndex = detailPosition.yPosition; heightIndex >  (-tetraminoHeight); heightIndex--)
	{
		detailPosition.yPosition = heightIndex;
		detailWithNewPosition->setDetailPosition(detailPosition);

		if (checkCollisionWithDetailsAndBorders(detailWithNewPosition))
		{
			detailPosition.yPosition = detailPosition.yPosition + 1;
			break;
		}
	}

 	delete detailWithNewPosition;
	return detailPosition;
}

bool CollisionDelegate::checkCollisionWithDetailsAndBorders(TetraminoDetail *aDetail)
{
	bool collision = checkCollisionDetailWithOtherTetraminos(aDetail);
	bool collisionWithBoard = checkCollisionDetailWithGameBorders(aDetail);
	return (collision || collisionWithBoard);
}
