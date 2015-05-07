#include "GameStatesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTransitionsViewController.h"
#include "GamePopUpsController.h"
#include "GameAnalyticController.h"

GameStatesHelper::GameStatesHelper(void)
{
}


GameStatesHelper::~GameStatesHelper(void)
{
}

void GameStatesHelper::goToScene(GameState aState)
{
	GameTransitionsViewController *transitionsController = (GameTransitionsViewController*)ServiceLocator::getServiceForKey(gameTransitionsViewControllerKey);
	transitionsController->changeOnNewState(aState);

	GameAnalyticController *gameAnalyticController = (GameAnalyticController*)ServiceLocator::getServiceForKey(gameAnalyticControllerKey);
	gameAnalyticController->goToScreen(aState);
}

void GameStatesHelper::goToPopUp(PopUpType aPopUp)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gamePopUpsControllerKey);
	popUpsController->showPopUp(aPopUp);
}