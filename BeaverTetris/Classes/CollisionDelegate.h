#pragma once

#include "GameStructures.h"

class GameBoard;
class TetraminoDetail;

class CollisionDelegate
{
public:
	CollisionDelegate(GameBoard *aGameBoard);
	~CollisionDelegate(void);

	bool checkCollisionWithDetail(TetraminoDetail *aDetail);
	GamePositionOnBoard getCollisionPositionWithBoardForDetail(TetraminoDetail *aDetail);
	bool checkCollisionDetailWithGameBorders(TetraminoDetail *detailWithNewPosition);

private:

	GameBoard *_gameBoard;

	bool collisionWithDetailPositionAndDetail(GamePositionOnBoard aDetailPosition, TetraminoDetail *aDetail);

	bool detailOutBoard(TetraminoDetail *aDetail);
	bool checkCollisionWithDetailRow(int detailRow ,TetraminoDetail *aDetail);
	bool collisionWithPositionInDetail(GamePositionOnBoard aPosition, TetraminoDetail *aDetail);
	bool tetraminoInDetailOutBoard(GamePositionOnBoard aTetraminoAbsolutePosition, TetraminoDetail *aDetail);

};

