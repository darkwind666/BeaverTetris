#pragma once

#include "GameSystemInterface.h"

class WinGameSystem :public GameSystemInterface
{
public:
	WinGameSystem(void);
	~WinGameSystem(void);

	void updateSystem(float deltaTime);

};

