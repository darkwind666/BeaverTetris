#pragma once

class GameTimeStepController;

class TimeAccelerationEvent
{
public:
	TimeAccelerationEvent(void);
	~TimeAccelerationEvent(void);

	void updateEvent(void);

private:

	int _currentUpdateState;
	int _currentEventState;
	GameTimeStepController *_gameTimeStepController;
	bool _eventActive;

	void stepEventActive();
	void stepTimeInterval();

};

