#pragma once

#include "TetraminoDetail.h"
#include "GameBoard.h"

class CollisionDelegate
{
public:
	CollisionDelegate(GameBoard *aGameBoard);
	~CollisionDelegate(void);

	bool checkCollisionWithDetail(TetraminoDetail aDetail);

private:

	GameBoard *_gameBoard;

};

