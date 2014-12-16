#pragma once

#include "GameSystemInterface.h"

class RemovingDeadTetraminosSystem :public GameSystemInterface
{
public:
	RemovingDeadTetraminosSystem(void);
	~RemovingDeadTetraminosSystem(void);

	void updateSystem(float deltaTime);

};

