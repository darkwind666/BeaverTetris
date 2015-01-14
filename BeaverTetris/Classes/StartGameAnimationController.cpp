#include "StartGameAnimationController.h"
#include "StartGameMenuController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameViewConstants.h"

using namespace cocos2d;

StartGameAnimationController::StartGameAnimationController(void)
{
	_startGameMenuController = new StartGameMenuController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_startGameMenuController, this, startGameMenuKey);
}


StartGameAnimationController::~StartGameAnimationController(void)
{
}

void StartGameAnimationController::onEnterTransitionDidFinish()
{
	Vec2 finalMenuPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameMenuKey);
	CCAction *moveMenu = CCMoveTo::create(startMenuActionDuration, finalMenuPosition);
	_startGameMenuController->runAction(moveMenu);
}