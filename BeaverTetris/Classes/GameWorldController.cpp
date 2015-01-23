#include "GameWorldController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameWorldBackgroundController.h"
#include "GameBoardController.h"

GameWorldController::GameWorldController(void)
{
	_gameBoardController = new GameBoardController();
	makeControllerView();
}


GameWorldController::~GameWorldController(void)
{
}

void GameWorldController::makeControllerView()
{
	GameWorldBackgroundController *backgroundController = new GameWorldBackgroundController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundController, this, mainGameBackgroundControllerKey);

	CocosNodesHelper::addChildNodeToParentNodeWithKey(_gameBoardController, this, mainGameBoardControllerKey);
}

void GameWorldController::onEnterTransitionDidFinish()
{
	scheduleUpdate();
}

void GameWorldController::update(float delta)
{
	_gameBoardController->redrawGameBoard();
}