#include "CurrentGameEventsDataSource.h"
#include "TimeAccelerationEvent.h"
#include "TetraminosFallEvent.h"

using namespace std;

CurrentGameEventsDataSource::CurrentGameEventsDataSource(CurrentLevelDataSource *aCurrentLevelDataSource)
{
	_currentLevelDataSource = aCurrentLevelDataSource;
	_gameEvents = makeGameEvents();
}


CurrentGameEventsDataSource::~CurrentGameEventsDataSource(void)
{
}

bool CurrentGameEventsDataSource::availableEvent(void)
{
	bool availableEvent = false;

	vector<GameEventInterface*>::iterator gameEventsIterator;

	for (gameEventsIterator = _gameEvents.begin(); gameEventsIterator != _gameEvents.end(); gameEventsIterator++)
	{
		GameEventInterface *gameEvent = *gameEventsIterator;
		if (gameEvent->eventTime())
		{
			availableEvent = true;
			return availableEvent;
		}
	}
	return availableEvent;
}

void CurrentGameEventsDataSource::runAvailableEvent(void)
{
	vector<GameEventInterface*>::iterator gameEventsIterator;
	
	for (gameEventsIterator = _gameEvents.begin(); gameEventsIterator != _gameEvents.end(); gameEventsIterator++)
	{
		GameEventInterface *gameEvent = *gameEventsIterator;
		if (gameEvent->eventTime())
		{
			gameEvent->runEvent();
		}
	}
}

void CurrentGameEventsDataSource::updateEvents(void)
{
	vector<GameEventInterface*>::iterator gameEventsIterator;
	for (gameEventsIterator = _gameEvents.begin(); gameEventsIterator != _gameEvents.end(); gameEventsIterator++)
	{
		GameEventInterface *gameEvent = *gameEventsIterator;
		if (gameEvent->eventTime())
		{
			gameEvent->updateEvent();
		}
	}
}

void CurrentGameEventsDataSource::refreshDataSource()
{
	_gameEvents = makeGameEvents();
}

vector<GameEventInterface*> CurrentGameEventsDataSource::makeGameEvents()
{

	vector<GameEventInterface*> gameEvents;

	TimeAccelerationEvent *timeAccelerationEvent = new TimeAccelerationEvent();
	TetraminosFallEvent *tetraminosFallEvent = new TetraminosFallEvent();

	gameEvents.push_back(timeAccelerationEvent);
	gameEvents.push_back(tetraminosFallEvent);

	return gameEvents;

}