#pragma once

#include "ServiceInterface.h"
#include <string>
#include <map>
#include "EventHandlerInterface.h"
#include "GameStructures.h"
#include "GameEnums.h"

class EventDispatcher :public ServiceInterface
{
public:
	EventDispatcher(void);
	~EventDispatcher(void);

	void handleEvent(GameEvent aEvent);
	void setEventHandlerWithEventName(EventHandlerInterface *aEventHandler , EventType aEventType);
	void removeEventHandlerWithEventName(EventHandlerInterface *aEventHandler , EventType aEventType);

protected:

	std::map < EventType, EventHandlerInterface* > _handlers;

};

