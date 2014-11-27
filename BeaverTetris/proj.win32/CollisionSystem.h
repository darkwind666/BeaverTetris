#pragma once

#include "GameSystemInterface.h"
#include "GameBoard.h"
#include "ActiveDetails.h"

class CollisionSystem : public GameSystemInterface
{
public:
	CollisionSystem(GameBoard *aGameBoard, ActiveDetails *aActiveDetails);
	~CollisionSystem(void);

	void updateSystem(float deltaTime);

};

