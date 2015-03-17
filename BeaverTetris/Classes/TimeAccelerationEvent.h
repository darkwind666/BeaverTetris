#pragma once

class GameTimeStepController;

class TimeAccelerationEvent
{
public:
	TimeAccelerationEvent(int aInterval, int aEventDuration);
	~TimeAccelerationEvent(void);

	void updateEvent(void);

private:

	int _eventInterval;
	int _eventDuration;
	int _currentUpdateState;
	int _currentEventState;
	GameTimeStepController *_gameTimeStepController;
	bool _eventActive;

	void stepEventActive();
	void stepTimeInterval();

};

