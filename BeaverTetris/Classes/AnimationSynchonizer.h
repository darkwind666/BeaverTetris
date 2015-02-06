#pragma once

#include "cocos2d.h"

class GameTimeStepController;

class AnimationSynchonizer : public cocos2d::Node
{
public:
	AnimationSynchonizer(void);
	~AnimationSynchonizer(void);

	void updateSynchonizer();
	void addAnimationToQueue(cocos2d::FiniteTimeAction* aAnimation);

private:

	GameTimeStepController *_gameTimeStepController;
	cocos2d::FiniteTimeAction* _animationsQueue;

};

