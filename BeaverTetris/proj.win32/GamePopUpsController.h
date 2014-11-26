#pragma once

#include "EventHandlerInterface.h"
#include <map>

class GamePopUpsController :public EventHandlerInterface
{
public:

	GamePopUpsController(void);
	~GamePopUpsController(void);

	void handleEventWithInformation(GameEvent aEvent);

private:

	typedef void (GamePopUpsController::*handlerFunctionPointer) (void);

	std::map <EventType, handlerFunctionPointer> _eventHandlers;
	GameEventInformation _eventInformation;

	void showPopUp(void);
	void closePopUp(void);

};

