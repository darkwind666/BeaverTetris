#include "StartGameAnimationController.h"
#include "StartGameMenuController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

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

}