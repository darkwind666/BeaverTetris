#include "GameTimeStepController.h"
#include "GameDesignConstants.h"
#include "GameSystemInterface.h"

using namespace std;

GameTimeStepController::GameTimeStepController(void)
{
	_updateInterval = normalUpdateInterval;
	_updateAvailable = false;
	_currentTimeInterval = 0;
	_systems = vector<GameSystemInterface*>();
	setAllSystemsUpdated();
}

GameTimeStepController::~GameTimeStepController(void)
{
}

void GameTimeStepController::setAllSystemsUpdated()
{
	_currentSystemIndex = 0;
	_updateSystems = false;
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
		if (_updateSystems)
		{
			updateNextSystem(deltaTime);
		}
		else
		{
			countTimeStep(deltaTime);
		}
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
		if (_updateAvailable == false)
		{
			_updateSystems = true;
			_currentSystemIndex = distance(_systems.begin(), systemsIterator);
			break;
		}
	}
}

void GameTimeStepController::updateNextSystem(float deltaTime)
{
	_currentSystemIndex++;
	if (_currentSystemIndex < _systems.size())
	{
		stepNextSystems(deltaTime);
	}
	else
	{
		setAllSystemsUpdated();
	}
}

void GameTimeStepController::stepNextSystems(float deltaTime)
{
	vector<GameSystemInterface*>::iterator systemsIterator;
	for (systemsIterator = _systems.begin() + _currentSystemIndex; systemsIterator != _systems.end(); systemsIterator++)
	{
		GameSystemInterface *system = *systemsIterator;
		system->updateSystem(deltaTime);
		if (_updateAvailable == false)
		{
			_currentSystemIndex = distance(_systems.begin(), systemsIterator);
			break;
		}
	}
	if (systemsIterator == _systems.end())
	{
		setAllSystemsUpdated();
	}
}

