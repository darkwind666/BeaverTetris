#pragma once

#include "GameStructures.h"

class EventHandlerInterface
{
public:
	virtual void handleEventWithInformation(GameEventInformation aEventInformation) = 0;
};

