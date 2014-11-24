#include "EventDispatcher.h"

using namespace std;

EventDispatcher::EventDispatcher(void)
{
	_handlers = map <EventType, EventHandlerInterface*>();
}


EventDispatcher::~EventDispatcher(void)
{
}

void EventDispatcher::handleEvent(GameEvent aEvent) 
{
	EventHandlerInterface *eventHandler = _handlers[aEvent.eventType];
	eventHandler->handleEventWithInformation(aEvent);
} 

void EventDispatcher::setEventHandlerWithEventName(EventHandlerInterface *aEventHandler , EventType aEventType) 
{
	_handlers[aEventType] = aEventHandler;
}

void EventDispatcher::removeEventHandlerWithEventName(EventHandlerInterface *aEventHandler , EventType aEventType)
{
	_handlers.erase(aEventType);
}