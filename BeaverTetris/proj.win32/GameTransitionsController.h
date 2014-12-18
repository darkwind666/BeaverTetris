#pragma once

#include "EventHandlerInterface.h"
#include "ServiceInterface.h"
#include "GameTransitionsViewController.h"
#include <map>
#include "PlayerSelectionDataSource.h"

class GameTransitionsController :public EventHandlerInterface, ServiceInterface
{
public: 
	GameTransitionsController(GameTransitionsViewController *aGameTransitionsViewController, PlayerSelectionDataSource *aPlayerSelectionDataSource);
	~GameTransitionsController(void);

	void handleEventWithInformation(GameEvent aEvent);

private:

	typedef void (GameTransitionsController::*handlerFunctionPointer) (void);

	GameTransitionsViewController *_gameTransitionsViewController;
	PlayerSelectionDataSource *_playerSelectionDataSource;
	std::map <EventType, handlerFunctionPointer> _eventHandlers;
	GameEventInformation _eventInformation;
	
	void goToInitialState(void);
	void changeState(void);
	void goToPreviousState(void);
	void goToNextLevel(void);

};

