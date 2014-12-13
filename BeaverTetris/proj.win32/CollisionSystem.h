#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "ActiveDetails.h"
#include "GameFlowSystem.h"

class CollisionDelegate;

class CollisionSystem : public GameSystemInterface
{
public:
	CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails, GameFlowSystem *aGameFlowController);
	~CollisionSystem(void);

	void updateSystem(float deltaTime);

private:

	ActiveDetails *_activeDetailsStore;
	GameBoard *_gameBoard;
	GameFlowSystem *_gameFlowController;
	CollisionDelegate *_collisionDelegate;

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

};

