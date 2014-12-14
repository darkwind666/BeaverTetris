#pragma once

#include <vector>
#include "GameSystemInterface.h"

class GameSystemInterface;

class GameTimeStepController
{
public:
	GameTimeStepController(void);
	~GameTimeStepController(void);

	void setUpdateInterval(float aUpdateInterval);
	void update(float deltaTime);
	void addSystem(GameSystemInterface *aSystem);

private:

	float _updateInterval;
	int _currentTimeInterval;
	std::vector<GameSystemInterface*> _systems;

};

