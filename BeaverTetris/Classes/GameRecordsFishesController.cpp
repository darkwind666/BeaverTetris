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
	_fish2->setScale(0.7f);
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
	FiniteTimeAction *moveDownFish1 = MoveTo::create(bigFishActionDuration, leftFish1Position);
	FiniteTimeAction *moveUpFish1 = MoveTo::create(bigFishActionDuration, _fish1->getPosition());
	Sequence *sequence = Sequence::create(moveDownFish1, moveUpFish1, nullptr);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish1->runAction(repeat);
}

void GameRecordsFishesController::runFish2Animation()
{
	Vec2 leftFish2Position = GameElementsDataHelper::getElementFinalActionPositionForKey(gameRecordsFish2Key);
	FiniteTimeAction *moveDownFish2 = MoveTo::create(crazyFishActionDuration, leftFish2Position);
	FiniteTimeAction *moveUpFish1 = MoveTo::create(crazyFishActionDuration, _fish2->getPosition());
	Sequence *sequence = Sequence::create(moveDownFish2, moveUpFish1, nullptr);
	RepeatForever *repeat = RepeatForever::create(sequence);
	_fish2->runAction(repeat);
}

void GameRecordsFishesController::onExitTransitionDidStart()
{
	_fish1->stopAllActions();
	_fish2->stopAllActions();
}