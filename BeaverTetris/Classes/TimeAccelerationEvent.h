#pragma once

#include "ServiceInterface.h"

class GameTimeStepController;

class TimeAccelerationEvent : public ServiceInterface
{
public:
	TimeAccelerationEvent(int aInterval, int aEventDuration, int fallingSpeed);
	~TimeAccelerationEvent(void);

	void updateEvent(void);
	bool eventActive();
	int getAcceleratedUpdateInterval();

private:

	int _eventInterval;
	int _eventDuration;
	int _acceleratedUpdateInterval;
	int _currentUpdateState;
	int _currentEventState;
	GameTimeStepController *_gameTimeStepController;
	bool _eventActive;

	void stepEventActive();
	void stepTimeInterval();

};

