#include "GameFlowSystem.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "ServiceLocator.h"
#include "CurrentDetailDataSource.h"
#include "GameTimeStepController.h"
#include "TetraminosFallEvent.h"
#include "TimeAccelerationEvent.h"
#include "CurrentLevelDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

GameFlowSystem::GameFlowSystem(GameTimeStepController *aGameTimeStepController)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_gameTimeStepController = aGameTimeStepController;
	makeGameEvents();
}


GameFlowSystem::~GameFlowSystem(void)
{
	delete _timeAccelerationEvent;
}

void GameFlowSystem::makeGameEvents()
{
	_tetraminosFallEvent = NULL;
	_timeAccelerationEvent = NULL;
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	GameLevelInformation levelData = currentLevelDataSource->getCurrentLevelData();
	vector<GameEventInformation> availableEvents = levelData.availableEvents;
	makeEventsWithData(availableEvents);
}

void GameFlowSystem::makeEventsWithData(vector<GameEventInformation> &availableEvents)
{
	makeFallDetailsEventWithData(availableEvents);
	makeAccelerationEventWithData(availableEvents);
}

void GameFlowSystem::makeFallDetailsEventWithData(vector<GameEventInformation> &availableEvents)
{
	if (findEventForTypeInEvents(kTetraminosFallEvent, availableEvents))
	{
		int eventIndex = getIndexForTypeInEvents(kTetraminosFallEvent, availableEvents);
		GameEventInformation eventData = availableEvents[eventIndex];
		TetraminosFallEvent *tetraminosFallEvent = new TetraminosFallEvent(eventData.eventInterval, eventData.detailsCount);
		_tetraminosFallEvent = tetraminosFallEvent;
		ServiceLocator::setServiceForKey(tetraminosFallEvent, tetraminosFallEventModelKey);
	}
}

void GameFlowSystem::makeAccelerationEventWithData(vector<GameEventInformation> &availableEvents)
{
	if (findEventForTypeInEvents(kTimeAccelerationEvent, availableEvents))
	{
		int eventIndex = getIndexForTypeInEvents(kTimeAccelerationEvent, availableEvents);
		GameEventInformation eventData = availableEvents[eventIndex];
		TimeAccelerationEvent *timeAccelerationEvent = new TimeAccelerationEvent(eventData.eventInterval, eventData.eventDuration, eventData.fallingSpeed);
		_timeAccelerationEvent = timeAccelerationEvent;
		ServiceLocator::setServiceForKey(timeAccelerationEvent, timeAccelerationEventModelKey);
	}
}

bool GameFlowSystem::findEventForTypeInEvents(GameEventType aType, vector<GameEventInformation> &availableEvents)
{
	bool find = false;
	vector<GameEventInformation>::iterator eventsIterator;
	for (eventsIterator = availableEvents.begin(); eventsIterator != availableEvents.end(); eventsIterator++)
	{
		GameEventInformation eventData = *eventsIterator;
		if (eventData.eventType == aType)
		{
			find = true;
			break;
		}
	}
	return find;
}

int GameFlowSystem::getIndexForTypeInEvents(GameEventType aType, vector<GameEventInformation> &availableEvents)
{
	int index = 0;
	vector<GameEventInformation>::iterator eventsIterator;
	for (eventsIterator = availableEvents.begin(); eventsIterator != availableEvents.end(); eventsIterator++)
	{
		GameEventInformation eventData = *eventsIterator;
		if (eventData.eventType == aType)
		{
			index = distance(availableEvents.begin(), eventsIterator);
			break;
		}
	}
	return index;
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
	updateEvents();
	runAvailableEvent();
}

void GameFlowSystem::updateEvents()
{
	if (_tetraminosFallEvent)
	{
		_tetraminosFallEvent->updateEvent();
	}
	if (_timeAccelerationEvent)
	{
		_timeAccelerationEvent->updateEvent();
	}
}

void GameFlowSystem::runAvailableEvent()
{
	if (_tetraminosFallEvent)
	{
		runFallEvent();
	}
	else
	{
		makeNewDetail();
	}
}

void GameFlowSystem::runFallEvent()
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
