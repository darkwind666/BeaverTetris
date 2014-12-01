#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "ActiveDetails.h"
#include "GameFlowController.h"

class CollisionDelegate;

class CollisionSystem : public GameSystemInterface
{
public:
	CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails, GameFlowController *aGameFlowController);
	~CollisionSystem(void);

	void updateSystem(float deltaTime);

private:

	ActiveDetails *_activeDetailsStore;
	GameBoard *_gameBoard;
	GameFlowController *_gameFlowController;
	CollisionDelegate *_collisionDelegate;

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

};

