#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "ActiveDetails.h"

class CollisionDelegate;

class CollisionSystem : public GameSystemInterface
{
public:
	CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails);
	~CollisionSystem(void);

	void updateSystem(float deltaTime);

private:

	ActiveDetails *_activeDetailsStore;
	GameBoard *_gameBoard;
	CollisionDelegate *_collisionDelegate;

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

};

