#include "GameTimeStepController.h"
#include "GameDesignConstants.h"
#include "GameSystemInterface.h"

using namespace std;

GameTimeStepController::GameTimeStepController(void)
{
	_updateInterval = normalUpdateInterval;
	_updateAvailable = true;
	_currentTimeInterval = 0;
	_systems = vector<GameSystemInterface*>();
}

GameTimeStepController::~GameTimeStepController(void)
{
}

void GameTimeStepController::setUpdateInterval(float aUpdateInterval)
{
	_updateInterval = aUpdateInterval;
	_currentTimeInterval = 0;
}

void GameTimeStepController::setUpdateAvailable(bool updateAvailable)
{
	_updateAvailable = updateAvailable;
}

bool GameTimeStepController::getUpdataAvailable()
{
	return _updateAvailable;
}

void GameTimeStepController::addSystem(GameSystemInterface *aSystem)
{
	_systems.push_back(aSystem);
}

void GameTimeStepController::update(float deltaTime)
{
	if (_updateAvailable)
	{
		countTimeStep(deltaTime);
	}
}

void GameTimeStepController::countTimeStep(float deltaTime)
{
	if (_currentTimeInterval >= _updateInterval)
	{
		updateSystems(deltaTime);
		_currentTimeInterval = 0;
	}
	_currentTimeInterval++;
}


void GameTimeStepController::updateSystems(float deltaTime)
{
	vector<GameSystemInterface*>::iterator systemsIterator;
	for (systemsIterator = _systems.begin(); systemsIterator != _systems.end(); systemsIterator++)
	{
		GameSystemInterface *system = *systemsIterator;
		system->updateSystem(deltaTime);
	}
}


