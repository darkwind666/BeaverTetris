#pragma once

#include "GameStructures.h"

class EventHandlerInterface
{
public:
	virtual void handleEventWithInformation(GameEvent aEvent) = 0;
};

