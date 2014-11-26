#include "GamePopUpsController.h"

using namespace std;

GamePopUpsController::GamePopUpsController(void)
{
	_eventHandlers = map <EventType, handlerFunctionPointer>();
	_eventHandlers[kGoToPopUp] = &GamePopUpsController::showPopUp;
	_eventHandlers[kClosePopUp] = &GamePopUpsController::closePopUp;
}


GamePopUpsController::~GamePopUpsController(void)
{
}



void GamePopUpsController::handleEventWithInformation(GameEvent aEvent) 
{
	_eventInformation = aEvent.eventInformation;
	handlerFunctionPointer function = _eventHandlers[aEvent.eventType];
	(this->*function)();
}


void GamePopUpsController::showPopUp(void)
{

}

void GamePopUpsController::closePopUp(void)
{

}