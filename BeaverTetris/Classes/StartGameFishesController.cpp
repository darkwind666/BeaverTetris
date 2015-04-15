#include "StartGameFishesController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

StartGameFishesController::StartGameFishesController(void)
{
	_fish1 = CocosNodesHelper::getSpriteWithKey(startGameFish1Key);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_fish1, this, startGameFish1Key);

	_fish2 = CocosNodesHelper::getSpriteWithKey(startGameFish2Key);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_fish2, this, startGameFish2Key);

	_fish3 = CocosNodesHelper::getSpriteWithKey(startGameFish3Key);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_fish3, this, startGameFish3Key);
}


StartGameFishesController::~StartGameFishesController(void)
{
}

void StartGameFishesController::onEnterTransitionDidFinish()
{
	runFish1Animation();
	runFish2Animation();
	runFish3Animation();
}

void StartGameFishesController::runFish1Animation()
{
	Vec2 leftFish1Position = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameFish1Key);
	FiniteTimeAction *moveLeftFish1 = MoveTo::create(bigFishActionDuration, leftFish1Position);
	FiniteTimeAction *flipRightAction = FlipX::create(true);
	FiniteTimeAction *moveRightFish1 = MoveTo::create(bigFishActionDuration, _fish1->getPosition());
	FiniteTimeAction *flipLeftAction = FlipX::create(false);
	Sequence *sequence = Sequence::create(moveLeftFish1, flipRightAction, moveRightFish1, flipLeftAction, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish1->runAction(repeat);
}

void StartGameFishesController::runFish2Animation()
{
	Vec2 leftFish2Position = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameFish2Key);
	FiniteTimeAction *moveRightFish1 = MoveTo::create(middleFishActionDuration, _fish2->getPosition());
	FiniteTimeAction *flipLeftAction = FlipX::create(true);
	FiniteTimeAction *moveLeftFish1 = MoveTo::create(middleFishActionDuration, leftFish2Position);
	FiniteTimeAction *flipRightAction = FlipX::create(false);
	Sequence *sequence = Sequence::create(moveRightFish1, flipLeftAction, moveLeftFish1, flipRightAction, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish2->runAction(repeat);
}

void StartGameFishesController::runFish3Animation()
{
	Vec2 leftFish2Position = GameElementsDataHelper::getElementFinalActionPositionForKey(startGameFish3Key);
	FiniteTimeAction *moveRightFish1 = MoveTo::create(crazyFishActionDuration, _fish3->getPosition());
	FiniteTimeAction *flipLeftAction = FlipX::create(true);
	FiniteTimeAction *moveLeftFish1 = MoveTo::create(crazyFishActionDuration, leftFish2Position);
	FiniteTimeAction *flipRightAction = FlipX::create(false);
	Sequence *sequence = Sequence::create(moveRightFish1, flipLeftAction, moveLeftFish1, flipRightAction, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish3->runAction(repeat);
}

void StartGameFishesController::onExitTransitionDidStart()
{
	_fish1->stopAllActions();
	_fish2->stopAllActions();
	_fish3->stopAllActions();
}