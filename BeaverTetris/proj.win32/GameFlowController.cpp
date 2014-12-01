#include "GameFlowController.h"


GameFlowController::GameFlowController(CurrentDetailController *aCurrentDetailController)
{
	_currentDetailController = aCurrentDetailController;
}


GameFlowController::~GameFlowController(void)
{
}

void GameFlowController::makeNewGameEvent()
{
	_currentDetailController->makeNewDetail();
}
