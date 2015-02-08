#include "GameFlowSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "GameTimeStepController.h"

using namespace std;

GameFlowSystem::GameFlowSystem()
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
}


GameFlowSystem::~GameFlowSystem(void)
{

}

void GameFlowSystem::updateSystem(float deltaTime)
{
	if (_currentDetailDataSource->currentDetailAvailable() == false && _gameTimeStepController->getUpdataAvailable() == true)
	{
		_currentDetailDataSource->makeNewDetail();
	}
}
