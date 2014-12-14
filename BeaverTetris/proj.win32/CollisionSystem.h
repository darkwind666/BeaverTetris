#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "ActiveDetails.h"
#include "TetraminoDetailLocatorDelegate.h"

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
	TetraminoDetailLocatorDelegate *_tetraminoDetailLocatorDelegate;

	void writeTetraminoDetailInBoard(TetraminoDetail *aTetraminoDetail);

};

