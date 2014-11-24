#pragma once

#include "EventHandlerInterface.h"

class GamePopUpsController :public EventHandlerInterface
{
public:

	GamePopUpsController(void);
	~GamePopUpsController(void);

	void handleEventWithInformation(GameEvent aEvent);

private:

	void showPopUp(void);
	void closePopUp(void);

};

