#include "GameFlowSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "GameTimeStepController.h"
#include "TetraminosFallEvent.h"
#include "TimeAccelerationEvent.h"

using namespace std;

GameFlowSystem::GameFlowSystem()
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	TetraminosFallEvent *tetraminosFallEvent = new TetraminosFallEvent();
	_tetraminosFallEvent = tetraminosFallEvent;
	ServiceLocator::setServiceForKey(tetraminosFallEvent, tetraminosFallEventModelKey);
	_timeAccelerationEvent = new TimeAccelerationEvent();
}


GameFlowSystem::~GameFlowSystem(void)
{
	delete _timeAccelerationEvent;
}

void GameFlowSystem::updateSystem(float deltaTime)
{
	if (_gameTimeStepController->getUpdataAvailable() == true)
	{
		updateGameFlow();
	}
}

void GameFlowSystem::updateGameFlow()
{
	srand(time(0));
	_tetraminosFallEvent->updateEvent();
	_timeAccelerationEvent->updateEvent();
	runAvailableEvent();
}

void GameFlowSystem::runAvailableEvent()
{
	if (_tetraminosFallEvent->eventAvailable() && _currentDetailDataSource->currentDetailAvailable() == false)
	{
		_tetraminosFallEvent->runEvent();
	}
	else
	{
		makeNewDetail();
	}
}

void GameFlowSystem::makeNewDetail()
{
	if (_currentDetailDataSource->currentDetailAvailable() == false)
	{
		_currentDetailDataSource->makeNewDetail();
	}
}
