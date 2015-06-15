#pragma once

#include "cocos2d.h"

class FinalSceneAnimationController : public cocos2d::Node
{
public:
	FinalSceneAnimationController(void);
	~FinalSceneAnimationController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

private:

	cocos2d::Node *_finalSceneClock;
	cocos2d::Node *_finalSceneBeaver;
	cocos2d::Node *_finalSceneBeaverLeftHand;
	cocos2d::Node *_finalSceneBeaverRightHand;
	cocos2d::Node *_finalSceneBeaverEyes;

	cocos2d::Node* makeBeaver();
	cocos2d::Node* makeBeaverEyes();

	cocos2d::FiniteTimeAction* getBeaverAppearance();
	cocos2d::FiniteTimeAction* getBeaverJump();
	cocos2d::FiniteTimeAction* getCatchClockAnimation();
	cocos2d::FiniteTimeAction* getBeaverEyesAnimation();
	cocos2d::FiniteTimeAction* getBeaverHandsAnimation();
	void runAnimationForHand(cocos2d::Node* aHand);

};

