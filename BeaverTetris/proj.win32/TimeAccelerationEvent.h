#pragma once

#include "GameEventInterface.h"

class TimeAccelerationEvent :public GameEventInterface
{
public:
	TimeAccelerationEvent(void);
	~TimeAccelerationEvent(void);

	bool eventTime(void);
	void runEvent(void);
	void updateEvent(void);

};

