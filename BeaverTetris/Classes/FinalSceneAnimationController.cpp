#include "FinalSceneAnimationController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

FinalSceneAnimationController::FinalSceneAnimationController(void)
{
	Sprite *clock = CocosNodesHelper::getSpriteWithKey(finalScreenClockKey);
	_finalSceneClock = clock;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(clock, this, finalScreenClockKey);

	Node *beaver = makeBeaver();
	_finalSceneBeaver = beaver;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaver, this, finalScreenBeaverKey);
}


FinalSceneAnimationController::~FinalSceneAnimationController(void)
{
}

Node* FinalSceneAnimationController::makeBeaver()
{
	Node *beaver = Node::create();

	Sprite *beaverRightHand = CocosNodesHelper::getSpriteWithKey(finalScreenBeaverRightHandKey);
	beaverRightHand->setAnchorPoint(Vec2(0.35f,0.15f));
	_finalSceneBeaverRightHand = beaverRightHand;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverRightHand, beaver, finalScreenBeaverRightHandKey);
	
	Sprite *beaverLeftHand = CocosNodesHelper::getSpriteWithKey(finalScreenBeaverLeftHandKey);
	beaverLeftHand->setAnchorPoint(Vec2(0.25f,0.15f));
	_finalSceneBeaverLeftHand = beaverLeftHand;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverLeftHand, beaver, finalScreenBeaverLeftHandKey);

	Sprite *beaverBody = CocosNodesHelper::getSpriteWithKey(finalScreenBeaverBodyKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverBody, beaver, finalScreenBeaverBodyKey);
	
	Node *beaverEyes = makeBeaverEyes();
	_finalSceneBeaverEyes = beaverEyes;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverEyes, beaver, finalScreenBeaverEyesKey);
	

	return beaver;
}

Node* FinalSceneAnimationController::makeBeaverEyes()
{
	Node *beaverEyes = Node::create();

	Sprite *beaverRightEye = CocosNodesHelper::getSpriteWithKey(finalScreenBeaverRightEyeKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverRightEye, beaverEyes, finalScreenBeaverRightEyeKey);

	Sprite *beaverLeftEye = CocosNodesHelper::getSpriteWithKey(finalScreenBeaverLeftEyeKey);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaverLeftEye, beaverEyes, finalScreenBeaverLeftEyeKey);

	return beaverEyes;
}

void FinalSceneAnimationController::onEnterTransitionDidFinish()
{
	FiniteTimeAction *beaverAppearance = getBeaverAppearance();
	FiniteTimeAction *beaverJump = getBeaverJump();
	FiniteTimeAction *beaverEyesAnimation = getBeaverEyesAnimation();
	FiniteTimeAction *beaverHandsAnimation = getBeaverHandsAnimation();
	FiniteTimeAction *sequence = Sequence::create(beaverAppearance, beaverJump, beaverEyesAnimation, beaverHandsAnimation, nullptr);
	_finalSceneBeaver->runAction(sequence);
}

FiniteTimeAction* FinalSceneAnimationController::getBeaverAppearance()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(finalScreenBeaverKey);
	Vec2 beaverJumpOffset = GameElementsDataHelper::getElementOffsetForKey(finalScreenBeaverKey);
	ActionInterval *beaverJump = JumpTo::create(beaverStartScreenActionDuration, finalBeaverPosition, beaverJumpOffset.y, 1);
	FiniteTimeAction *actionWithBeaver = TargetedAction::create(_finalSceneBeaver, beaverJump);
	return actionWithBeaver;
}

FiniteTimeAction* FinalSceneAnimationController::getBeaverJump()
{
	Vec2 finalBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(finalScreenBeaverBodyKey);
	Vec2 startBeaverPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(finalScreenBeaverKey);
	FiniteTimeAction *moveUp = MoveTo::create(0.9f, finalBeaverPosition);
	FiniteTimeAction *catchClockAnimation = getCatchClockAnimation();
	FiniteTimeAction *moveDown = MoveTo::create(0.9f, startBeaverPosition);
	FiniteTimeAction *sequence = Sequence::create(moveUp, catchClockAnimation, moveDown, nullptr);
	FiniteTimeAction *actionWithBeaver = TargetedAction::create(_finalSceneBeaver, sequence);
	return actionWithBeaver;
}

FiniteTimeAction* FinalSceneAnimationController::getCatchClockAnimation()
{
	FiniteTimeAction *callback = CallFunc::create([this](){
		Vec2 clockPositionInHand = _finalSceneBeaverRightHand->convertToNodeSpace(_finalSceneClock->getPosition());
		_finalSceneClock->setPosition(clockPositionInHand);
		_finalSceneClock->retain();
		_finalSceneClock->removeFromParentAndCleanup(false);
		_finalSceneBeaverRightHand->addChild(_finalSceneClock);
		_finalSceneClock->release();
	});
	return callback;
}

FiniteTimeAction* FinalSceneAnimationController::getBeaverEyesAnimation()
{
	FiniteTimeAction *callback = CallFunc::create([this](){
		FiniteTimeAction *closeEyes = Hide::create();
		FiniteTimeAction *delayBetweeneSparks = DelayTime::create(0.1f);
		FiniteTimeAction *openEyes = Show::create();
		FiniteTimeAction *delay = DelayTime::create(1.0f);
		ActionInterval *sequence = Sequence::create(closeEyes, delayBetweeneSparks, openEyes, delay, nullptr);
		FiniteTimeAction *repeat = RepeatForever::create(sequence);
		_finalSceneBeaverEyes->runAction(repeat);
	});
	FiniteTimeAction *actionWithEyes = TargetedAction::create(this, callback);
	return actionWithEyes;
}

FiniteTimeAction* FinalSceneAnimationController::getBeaverHandsAnimation()
{
	FiniteTimeAction *callback = CallFunc::create([this](){
		runAnimationForHand(_finalSceneBeaverLeftHand);
		runAnimationForHand(_finalSceneBeaverRightHand);
	});
	FiniteTimeAction *actionWithHands = TargetedAction::create(this, callback);
	return actionWithHands;
}

void FinalSceneAnimationController::runAnimationForHand(Node* aHand)
{
	float duration = 0.9;
	FiniteTimeAction *rotateLeftHandUp = RotateTo::create(duration, 20);
	FiniteTimeAction *rotateLeftHandDown = RotateTo::create(duration, -20);
	ActionInterval *leftHandSequence = Sequence::create(rotateLeftHandUp, rotateLeftHandDown, nullptr);
	FiniteTimeAction *leftHandRepeat = RepeatForever::create(leftHandSequence);
	aHand->runAction(leftHandRepeat);
}

void FinalSceneAnimationController::onExitTransitionDidStart()
{
	_finalSceneBeaverEyes->stopAllActions();
	_finalSceneBeaverRightHand->stopAllActions();
	_finalSceneBeaverLeftHand->stopAllActions();
}