#pragma once

#include "GameEventInterface.h"
#include "GameTimeStepController.h"

class TimeAccelerationEvent :public GameEventInterface
{
public:
	TimeAccelerationEvent(void);
	~TimeAccelerationEvent(void);

	bool eventTime(void);
	void runEvent(void);
	void updateEvent(void);

private:

	int _currentUpdateState;
	int _currentEventState;
	GameTimeStepController *_gameTimeStepController;

};

