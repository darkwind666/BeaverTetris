#include "GameHudsController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "PlayerActionControllerFactory.h"

using namespace cocos2d;

GameHudsController::GameHudsController(void)
{
	makeView();
}


GameHudsController::~GameHudsController(void)
{
}

void GameHudsController::makeView()
{
	LayerColor *hudBackground = LayerColor::create(Color4B::GRAY, 100, 480);
	hudBackground->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(hudBackground, this, gameHudBackgroundKey);

	PlayerActionControllerFactory playerActionControllerFactory;
	Node *playerActionController = playerActionControllerFactory.getPlayerActionControllerForCurrentPlatform();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(playerActionController, this, playerActionControllerKey);
}