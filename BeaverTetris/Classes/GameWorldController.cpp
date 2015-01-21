#include "GameWorldController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameWorldBackgroundController.h"

GameWorldController::GameWorldController(void)
{
	makeControllerView();
}


GameWorldController::~GameWorldController(void)
{
}

void GameWorldController::makeControllerView()
{
	GameWorldBackgroundController *backgroundController = new GameWorldBackgroundController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(backgroundController, this, mainGameBackgroundControllerKey);
}