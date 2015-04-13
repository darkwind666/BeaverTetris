#include "LoadingGameWaveController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;

LoadingGameWaveController::LoadingGameWaveController(void)
{
}


LoadingGameWaveController::~LoadingGameWaveController(void)
{
}

void LoadingGameWaveController::onEnterTransitionDidFinish()
{
	makeWavesView();
	Action *wavesAction = getWavesAction();
	this->runAction(wavesAction);
}

void LoadingGameWaveController::makeWavesView()
{
	Sprite *leftWave = CocosNodesHelper::getSpriteWithKey(loadingGameWaveKey);
	leftWave->setAnchorPoint(Vec2(1.0f, 0.5f));
	this->addChild(leftWave);
	
	Sprite *rightWave = CocosNodesHelper::getSpriteWithKey(loadingGameWaveKey);
	rightWave->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->addChild(rightWave);
}

Action* LoadingGameWaveController::getWavesAction()
{
	Vec2 upDirectionoffset = Vec2(30.0f, 0.0f);
	Vec2 backDirectionoffset = Vec2(-30.0f, 0.0f);
	ActionInterval *moveRight = MoveBy::create(wavesActionDuration, upDirectionoffset);
	ActionInterval *moveToStartPlace = MoveBy::create(wavesActionDuration, backDirectionoffset);
	ActionInterval *moveLeft = MoveBy::create(wavesActionDuration, backDirectionoffset);
	ActionInterval *moveBackToStartPlace = MoveBy::create(wavesActionDuration, upDirectionoffset);
	
	Sequence *sequence = Sequence::create(moveRight, moveToStartPlace, moveLeft, moveBackToStartPlace, NULL);
	RepeatForever *repeat = RepeatForever::create(sequence);
	return repeat;
}

void LoadingGameWaveController::onExitTransitionDidStart()
{
	this->stopAllActions();
}

