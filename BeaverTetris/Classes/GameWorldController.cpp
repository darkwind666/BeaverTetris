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
	_gameStarted = false;
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

void GameWorldController::startGame()
{
	_gameTimeStepController->setUpdateAvailable(true);
	_gameStarted = true;
	scheduleUpdate();
}

void GameWorldController::onEnterTransitionDidFinish()
{
	_backgroundController->onEnterTransitionDidFinish();
}

void GameWorldController::update(float delta)
{
	_gameTimeStepController->update(delta);
	_gameWorldAnimationController->updateAnimation();
	_gameBoardController->redrawGameBoard();
}

void GameWorldController::pauseGameWorld()
{
	if (_gameStarted)
	{
		unscheduleUpdate();
	}
}

void GameWorldController::resumeGameWorld()
{
	if (_gameStarted)
	{
		scheduleUpdate();
	}
}