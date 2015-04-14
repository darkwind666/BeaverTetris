#include "StartGameAnimationController.h"
#include "StartGameMenuController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

StartGameAnimationController::StartGameAnimationController(void)
{
	_startGameMenuController = new StartGameMenuController();
	_beaver = CocosNodesHelper::getSpriteWithKey(startGameBeaverKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_startGameMenuController, this, startGameMenuKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_beaver, this, startGameBeaverKey);
}


StartGameAnimationController::~StartGameAnimationController(void)
{
}

void StartGameAnimationController::onEnterTransitionDidFinish()
{
	
	FiniteTimeAction *actionWithMenu = getAnimationWithMenu();
	FiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();

	Action *sequence = Sequence::create(actionWithMenu, actionWithBeaver, NULL);
	this->runAction(sequence);
}

FiniteTimeAction* StartGameAnimationController::getAnimationWithMenu()
{
	Vec2 finalMenuPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameMenuKey);
	ActionInterval *moveMenu = MoveTo::create(startMenuActionDuration, finalMenuPosition);
	FiniteTimeAction *ease = EaseBackOut::create(moveMenu);
	FiniteTimeAction *actionWithMenu = TargetedAction::create(_startGameMenuController, ease);
	return actionWithMenu;
}

FiniteTimeAction* StartGameAnimationController::getAnimationWithBeaver()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameBeaverKey);
	Vec2 beaverJumpOffset = GameElementsDataHelper::getElementOffsetForKey(startGameBeaverKey);
	ActionInterval *beaverJump = JumpTo::create(beaverStartScreenActionDuration, finalBeaverPosition, beaverJumpOffset.y, 1);
	FiniteTimeAction *actionWithBeaver = TargetedAction::create(_beaver, beaverJump);
	return actionWithBeaver;
}
