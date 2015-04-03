#include "GameWorldController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "GameWorldBackgroundController.h"
#include "GameBoardController.h"
#include "GameWorldAnimationController.h"
#include "GameTimeStepController.h"

GameWorldController::GameWorldController(void)
{
	_gameBoardController = new GameBoardController();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_gameWorldAnimationController =  new GameWorldAnimationController(_gameBoardController);
	_backgroundController = new GameWorldBackgroundController();
	makeControllerView();
}


GameWorldController::~GameWorldController(void)
{
}

void GameWorldController::makeControllerView()
{
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_backgroundController, this, mainGameBackgroundControllerKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_gameWorldAnimationController, this, mainGameAnimationControllerKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_gameBoardController, this, mainGameBoardControllerKey);
}

void GameWorldController::onEnterTransitionDidFinish()
{
	_backgroundController->onEnterTransitionDidFinish();
	scheduleUpdate();
}

void GameWorldController::update(float delta)
{
	_gameTimeStepController->update(delta);
	_gameWorldAnimationController->updateAnimation();
	_gameBoardController->redrawGameBoard();
}

void GameWorldController::pauseGameWorld()
{
	unscheduleUpdate();
}

void GameWorldController::resumeGameWorld()
{
	scheduleUpdate();
}