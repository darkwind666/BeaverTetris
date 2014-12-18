#include "GameTransitionsController.h"

using namespace std;

GameTransitionsController::GameTransitionsController(GameTransitionsViewController *aGameTransitionsViewController,  PlayerSelectionDataSource *aPlayerSelectionDataSource)
{
	_gameTransitionsViewController = aGameTransitionsViewController;
	_playerSelectionDataSource = aPlayerSelectionDataSource;
	_eventHandlers = map <EventType, handlerFunctionPointer>();
	_eventHandlers[kGoToInitualSceneEvent] = &GameTransitionsController::goToInitialState;
	_eventHandlers[kGoToSceneEvent] = &GameTransitionsController::changeState;
	_eventHandlers[kGoToPreviousSceneEvent] = &GameTransitionsController::goToPreviousState;
	_eventHandlers[kGoToNextLevelSceneEvent] = &GameTransitionsController::goToNextLevel;
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

void GameTransitionsController::goToInitialState(void)
{
	_gameTransitionsViewController->goToInitialState();
}

void GameTransitionsController::changeState(void)
{
	_gameTransitionsViewController->changeState();
}

void GameTransitionsController::goToPreviousState(void)
{
	_gameTransitionsViewController->goToPreviousState();
}

void GameTransitionsController::goToNextLevel(void)
{
	int selectedLevel = _playerSelectionDataSource->getSelectedGameLevel();
	_playerSelectionDataSource->selectGameLevel(selectedLevel + 1);
	_gameTransitionsViewController->changeState();
}