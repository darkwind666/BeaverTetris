#include "GameManager.h"
#include "GameDesignConstants.h"

using namespace std;

GameManager::GameManager(void)
{
	_updateInterval = normalUpdateInterval;
	_currentTimeInterval = 0;
	_systems = vector<GameSystemInterface*>();
}


GameManager::~GameManager(void)
{
}


void GameManager::setUpdateInterval(float aUpdateInterval)
{
	_updateInterval = aUpdateInterval;
	_currentTimeInterval = 0;

}

void GameManager::update(float deltaTime)
{
	if (_currentTimeInterval >= _updateInterval)
	{
		_currentTimeInterval = 0;
	}

	_currentTimeInterval++;

}

void GameManager::addSystem(GameSystemInterface *aSystem)
{
	_systems.push_back(aSystem);
}