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

	_beaver = CCSprite::create("HelloWorld.png");
	_beaver->setScale(0.3f);
	_beaver->setRotation(80);

	_beaverClockArrow = CCSprite::create("HelloWorld.png");
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
	
	CCFiniteTimeAction *actionWithMenu = getAnimationWithMenu();
	CCFiniteTimeAction *actionWithBeaver = getAnimationWithBeaver();
	CCFiniteTimeAction *actionWithClockArrow = getAnimationWithBeaverClockArrow();

	CCAction *sequence = CCSequence::create(actionWithMenu, actionWithBeaver, actionWithClockArrow, NULL);
	this->runAction(sequence);
}

CCFiniteTimeAction* StartGameAnimationController::getAnimationWithMenu()
{
	Vec2 finalMenuPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameMenuKey);
	CCActionInterval *moveMenu = CCMoveTo::create(startMenuActionDuration, finalMenuPosition);
	CCFiniteTimeAction *ease = CCEaseBackOut::create(moveMenu);
	CCFiniteTimeAction *actionWithMenu = CCTargetedAction::create(_startGameMenuController, ease);
	return actionWithMenu;
}

CCFiniteTimeAction* StartGameAnimationController::getAnimationWithBeaver()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameBeaverKey);
	Vec2 beaverJumpOffset = GameElementsDataHelper::getElementOffsetForKey(startGameBeaverKey);
	CCActionInterval *beaverJump = CCJumpTo::create(beaverStartScreenActionDuration, finalBeaverPosition, beaverJumpOffset.y, 1);
	CCFiniteTimeAction *actionWithBeaver = CCTargetedAction::create(_beaver, beaverJump);
	return actionWithBeaver;
}

CCFiniteTimeAction* StartGameAnimationController::getAnimationWithBeaverClockArrow()
{
	CCFiniteTimeAction *actionWithClockArrow = CCCallFunc::create([this](){
		CCActionInterval *rotateActionUp = CCRotateBy::create(beaverClockArrowRotationSpeed, 90);
		CCFiniteTimeAction *repeat = CCRepeatForever::create(rotateActionUp);
		_beaverClockArrow->runAction(repeat);
	});
	return actionWithClockArrow;
}
