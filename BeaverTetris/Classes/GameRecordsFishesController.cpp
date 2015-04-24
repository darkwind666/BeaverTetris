#include "GameRecordsFishesController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

GameRecordsFishesController::GameRecordsFishesController(void)
{
	_fish1 = CocosNodesHelper::getSpriteWithKey(gameRecordsFish1Key);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_fish1, this, gameRecordsFish1Key);

	_fish2 = CocosNodesHelper::getSpriteWithKey(gameRecordsFish2Key);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_fish2, this, gameRecordsFish2Key);
}


GameRecordsFishesController::~GameRecordsFishesController(void)
{
}

void GameRecordsFishesController::onEnterTransitionDidFinish()
{
	runFish1Animation();
	runFish2Animation();
}

void GameRecordsFishesController::runFish1Animation()
{
	Vec2 leftFish1Position = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsFish1Key);
	FiniteTimeAction *moveLeftFish1 = MoveTo::create(bigFishActionDuration, leftFish1Position);
	FiniteTimeAction *flipRightAction = FlipX::create(true);
	FiniteTimeAction *moveRightFish1 = MoveTo::create(bigFishActionDuration, _fish1->getPosition());
	FiniteTimeAction *flipLeftAction = FlipX::create(false);
	Sequence *sequence = Sequence::create(moveLeftFish1, flipRightAction, moveRightFish1, flipLeftAction, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish1->runAction(repeat);
}

void GameRecordsFishesController::runFish2Animation()
{
	Vec2 leftFish2Position = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsFish2Key);
	FiniteTimeAction *moveRightFish1 = MoveTo::create(middleFishActionDuration, _fish2->getPosition());
	FiniteTimeAction *flipLeftAction = FlipX::create(true);
	FiniteTimeAction *moveLeftFish1 = MoveTo::create(middleFishActionDuration, leftFish2Position);
	FiniteTimeAction *flipRightAction = FlipX::create(false);
	Sequence *sequence = Sequence::create(moveRightFish1, flipLeftAction, moveLeftFish1, flipRightAction, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish2->runAction(repeat);
}

void GameRecordsFishesController::onExitTransitionDidStart()
{
	_fish1->stopAllActions();
	_fish2->stopAllActions();
}