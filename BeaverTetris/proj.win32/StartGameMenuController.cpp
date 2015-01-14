#include "StartGameMenuController.h"
#include "StartGameMenuDataSource.h"

StartGameMenuController::StartGameMenuController(void)
{
	_startGameViewDataSource = new StartGameMenuDataSource();
}


StartGameMenuController::~StartGameMenuController(void)
{
}
