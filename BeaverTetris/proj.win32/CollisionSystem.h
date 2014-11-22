#pragma once

#include "GameSystemInterface.h"

class CollisionSystem : public GameSystemInterface
{
public:
	CollisionSystem(void);
	~CollisionSystem(void);

	void updateSystem(float deltaTime);

};

