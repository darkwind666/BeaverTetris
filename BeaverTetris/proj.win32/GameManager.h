#pragma once

#include <vector>
#include "GameSystemInterface.h"

class GameSystemInterface;

class GameManager
{
public:
	GameManager(void);
	~GameManager(void);

	void setUpdateInterval(float aUpdateInterval);
	void update(float deltaTime);
	void addSystem(GameSystemInterface *aSystem);

private:

	float _updateInterval;
	int _currentTimeInterval;
	std::vector<GameSystemInterface*> _systems;

};

