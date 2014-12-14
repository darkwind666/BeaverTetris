#include "GameTimeStepController.h"
#include "GameDesignConstants.h"

using namespace std;

GameTimeStepController::GameTimeStepController(void)
{
	_updateInterval = normalUpdateInterval;
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

void GameTimeStepController::update(float deltaTime)
{
	if (_currentTimeInterval >= _updateInterval)
	{
		_currentTimeInterval = 0;
	}

	_currentTimeInterval++;

}

void GameTimeStepController::addSystem(GameSystemInterface *aSystem)
{
	_systems.push_back(aSystem);
}