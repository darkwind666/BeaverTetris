#include "GameFlowSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;

GameFlowSystem::GameFlowSystem(CurrentDetailController *aCurrentDetailController, CurrentGameEventsDataSource *aCurrentGameEventsDataSource)
{
	_currentGameEventsDataSource = aCurrentGameEventsDataSource;
	_currentDetailController = aCurrentDetailController;
	_activeDetails = (ActiveDetails*)ServiceLocator::getServiceForKey(activeDetailsKey);
}


GameFlowSystem::~GameFlowSystem(void)
{

}

void GameFlowSystem::updateSystem(float deltaTime)
{
	vector<TetraminoDetail*> activeDetails = _activeDetails->getActiveDetails();
	if (activeDetails.size() <= 0)
	{
		if (_currentGameEventsDataSource->availableEvent())
		{
			_currentGameEventsDataSource->runAvailableEvent();
		}
		else
		{
			_currentDetailController->makeNewDetail();
		}

	}
	_currentGameEventsDataSource->updateEvents();
}
