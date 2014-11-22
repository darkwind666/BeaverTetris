#pragma once

#include "GameSystemInterface.h"

class MoveSystem :public GameSystemInterface
{
public:
	MoveSystem(void);
	~MoveSystem(void);

	void updateSystem(float deltaTime);

};

