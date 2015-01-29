#pragma once

#include "GameStructures.h"

class GameBoard;
class TetraminoDetail;

class CollisionDelegate
{
public:
	CollisionDelegate(GameBoard *aGameBoard);
	~CollisionDelegate(void);

	bool checkCollisionDetailWithOtherTetraminos(TetraminoDetail *aDetail);
	GamePositionOnBoard getCollisionPositionWithBoardForDetail(TetraminoDetail *aDetail);
	bool checkCollisionDetailWithGameBorders(TetraminoDetail *detailWithNewPosition);

private:

	GameBoard *_gameBoard;

	bool checkCollisionColumnWithOtherTetraminos(int aColumn, TetraminoDetail *aDetail);
	bool checkCollisionDetailWithOtherTetraminosOnPosition(TetraminoDetail *aDetail, GamePositionOnBoard aPosition);
	bool positionInBoard(GamePositionOnBoard aPosition);

	bool detailOutBoard(TetraminoDetail *aDetail);
	bool checkCollisionWithDetailRow(int detailRow ,TetraminoDetail *aDetail);
	bool collisionWithPositionInDetail(GamePositionOnBoard aPosition, TetraminoDetail *aDetail);
	bool tetraminoInDetailOutBoard(GamePositionOnBoard aTetraminoAbsolutePosition, TetraminoDetail *aDetail);
	bool checkCollisionWithDetailsAndBorders(TetraminoDetail *aDetail);

};

