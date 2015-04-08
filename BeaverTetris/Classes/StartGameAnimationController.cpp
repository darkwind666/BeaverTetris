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

	_beaver = Sprite::create("HelloWorld.png");
	_beaver->setScale(0.3f);
	_beaver->setRotation(80);

	_beaverClockArrow = Sprite::create("HelloWorld.png");
	_beaverClockArrow->setScaleX(0.2f);
	_beaverClockArrow->setScaleY(0.1f);
	_beaverClockArrow->setAnchorPoint(Vec2(0.0f, 0.5f));
	_beaverClockArrow->setColor(Color3B::YELLOW);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_beaverClockArrow, _beaver, startGameBeaverClockKey);

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
	FiniteTimeAction *actionWithClockArrow = getAnimationWithBeaverClockArrow();

	Action *sequence = Sequence::create(actionWithMenu, actionWithBeaver, actionWithClockArrow, NULL);
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

FiniteTimeAction* StartGameAnimationController::getAnimationWithBeaverClockArrow()
{
	FiniteTimeAction *actionWithClockArrow = CallFunc::create([this](){
		ActionInterval *rotateActionUp = RotateBy::create(beaverClockArrowRotationSpeed, 90);
		FiniteTimeAction *repeat = RepeatForever::create(rotateActionUp);
		_beaverClockArrow->runAction(repeat);
	});
	return actionWithClockArrow;
}
