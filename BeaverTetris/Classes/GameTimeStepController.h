#pragma once

#include "ServiceInterface.h"
#include <vector>

class GameSystemInterface;

class GameTimeStepController : public ServiceInterface
{
public:
	GameTimeStepController(void);
	~GameTimeStepController(void);

	void setUpdateInterval(float aUpdateInterval);
	void setUpdateAvailable(bool updateAvailable);
	bool getUpdataAvailable();
	void update(float deltaTime);
	void addSystem(GameSystemInterface *aSystem);

private:

	float _updateInterval;
	bool _updateAvailable;
	int _currentTimeInterval;
	std::vector<GameSystemInterface*> _systems;

	bool _updateSystems;
	int _currentSystemIndex;

	void countTimeStep(float deltaTime);
	void updateSystems(float deltaTime);
	void updateNextSystem(float deltaTime);
	void stepNextSystems(float deltaTime);
	void setAllSystemsUpdated();

};

