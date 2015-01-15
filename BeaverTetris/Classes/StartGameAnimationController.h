#pragma once

#include "cocos2d.h"

class StartGameMenuController;

class StartGameAnimationController : public cocos2d::CCNode
{
public:
	StartGameAnimationController(void);
	~StartGameAnimationController(void);

	virtual void onEnterTransitionDidFinish(); 

private:

	StartGameMenuController *_startGameMenuController;
	cocos2d::CCNode *_beaver;
	cocos2d::CCNode *_beaverClockArrow;

	cocos2d::CCFiniteTimeAction* getAnimationWithMenu();
	cocos2d::CCFiniteTimeAction* getAnimationWithBeaver();
	cocos2d::CCFiniteTimeAction* getAnimationWithBeaverClockArrow();

};

