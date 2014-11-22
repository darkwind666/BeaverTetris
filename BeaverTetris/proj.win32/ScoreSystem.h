#pragma once

#include "GameSystemInterface.h"

class ScoreSystem :public GameSystemInterface
{
public:
	ScoreSystem(void);
	~ScoreSystem(void);

	void updateSystem(float deltaTime);

};

