#include "GameStatesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTransitionsViewController.h"
#include "GamePopUpsController.h"

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
}

void GameStatesHelper::goToPopUp(PopUpType aPopUp)
{
	GamePopUpsController *popUpsController = (GamePopUpsController*)ServiceLocator::getServiceForKey(gameTransitionsViewControllerKey);
	popUpsController->showPopUp(aPopUp);
}