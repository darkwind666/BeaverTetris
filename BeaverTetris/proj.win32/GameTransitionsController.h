#pragma once

#include "EventHandlerInterface.h"
#include "ServiceInterface.h"
#include <vector>
#include <map>
#include "GameEnums.h"
#include "GameStructures.h"

class GameTransitionsController : public EventHandlerInterface, public ServiceInterface
{
public:
	GameTransitionsController(void);
	~GameTransitionsController(void);

	void handleEventWithInformation(GameEvent aEvent);

	void addSceneFactory();
	void addTransitionFromStateToState(GameState stateOne, GameState stateTwo, TransitionType transitionType);

private:

	typedef void (GameTransitionsController::*handlerFunctionPointer) (void);

	std::vector <GameState> _stateFactories;
	std::vector < std::vector <TransitionType> > _transitions;
	std::map <EventType, handlerFunctionPointer> _eventHandlers;
	GameEventInformation _eventInformation;

	void goToInitialState(void);
	void changeState(void);
	void goToPreviousState(void);

};