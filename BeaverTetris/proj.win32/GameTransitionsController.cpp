#include "GameTransitionsController.h"

using namespace std;

GameTransitionsController::GameTransitionsController(void)
{
	_eventHandlers = map <EventType, handlerFunctionPointer>();
	_eventHandlers[kGoToInitualSceneEvent] = &GameTransitionsController::goToInitialState;
	_eventHandlers[kGoToSceneEvent] = &GameTransitionsController::changeState;
	_eventHandlers[kGoToPreviousSceneEvent] = &GameTransitionsController::goToPreviousState;
}

GameTransitionsController::~GameTransitionsController(void)
{
}

void GameTransitionsController::handleEventWithInformation(GameEvent aEvent) 
{
	_eventInformation = aEvent.eventInformation;
	handlerFunctionPointer function = _eventHandlers[aEvent.eventType];
	(this->*function)();
}

void GameTransitionsController::addSceneFactory()
{
	
}


void GameTransitionsController::addTransitionFromStateToState(GameState stateOne, GameState stateTwo, TransitionType transitionType) 
{

}




void GameTransitionsController::goToInitialState(void)
{

}

void GameTransitionsController::changeState(void)
{

}

void GameTransitionsController::goToPreviousState(void)
{

}