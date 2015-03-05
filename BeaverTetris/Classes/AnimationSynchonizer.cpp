#include "AnimationSynchonizer.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "GameTimeStepController.h"

using namespace cocos2d;

AnimationSynchonizer::AnimationSynchonizer(void)
{
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_animationsQueue = NULL;
}

AnimationSynchonizer::~AnimationSynchonizer(void)
{
}

void AnimationSynchonizer::updateSynchonizer()
{
	int actionsCount = this->getNumberOfRunningActions();
	if (actionsCount == 0 && _animationsQueue != NULL)
	{
		FiniteTimeAction *startGameUpdate = CallFunc::create([this](){
			_gameTimeStepController->setUpdateAvailable(true);
			_animationsQueue = NULL;
		});
		Action *sequence = Sequence::create(_animationsQueue, startGameUpdate, NULL);
		this->runAction(sequence);
	}
}

void AnimationSynchonizer::addAnimationToQueue(cocos2d::FiniteTimeAction* aAnimation)
{
	_gameTimeStepController->setUpdateAvailable(false);
	if (_animationsQueue)
	{
		FiniteTimeAction *sequence = Sequence::create(_animationsQueue, aAnimation, NULL);
		_animationsQueue = sequence;
	}
	else
	{
		_animationsQueue = aAnimation;
	}
}