#pragma once

#include "EventHandlerInterface.h"

class GamePopUpsController :public EventHandlerInterface
{
public:

	GamePopUpsController(void);
	~GamePopUpsController(void);

	void handleEventWithInformation(GameEventInformation aEventInformation);

private:

	void showPopUp(void);
	void closePopUp(void);

};

