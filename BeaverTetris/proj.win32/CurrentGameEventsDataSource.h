#pragma once

#include "CurrentLevelDataSource.h"
#include "GameEventInterface.h"
#include <vector>

class CurrentGameEventsDataSource
{
public:
	CurrentGameEventsDataSource(CurrentLevelDataSource *aCurrentLevelDataSource);
	~CurrentGameEventsDataSource(void);

	bool availableEvent(void);
	void runAvailableEvent(void);
	void updateEvents(void);

	void refreshDataSource();

private:

	CurrentLevelDataSource *_currentLevelDataSource;
	std::vector<GameEventInterface*> _gameEvents;

	std::vector<GameEventInterface*> makeGameEvents();


};

