#include "GameFlowSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "GameTimeStepController.h"
#include "TetraminosFallEvent.h"

using namespace std;

GameFlowSystem::GameFlowSystem()
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_tetraminosFallEvent = new TetraminosFallEvent();
}


GameFlowSystem::~GameFlowSystem(void)
{

}

void GameFlowSystem::updateSystem(float deltaTime)
{
	srand(time(0));
	if (_gameTimeStepController->getUpdataAvailable() == true)
	{
		updateGameFlow();
	}
}

void GameFlowSystem::updateGameFlow()
{
	if (_currentDetailDataSource->currentDetailAvailable() == false)
	{
		_currentDetailDataSource->makeNewDetail();
	}
	_tetraminosFallEvent->updateEvent();
}
