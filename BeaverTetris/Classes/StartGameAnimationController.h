#pragma once

#include "cocos2d.h"

class StartGameMenuController;

class StartGameAnimationController : public cocos2d::Node
{
public:
	StartGameAnimationController(void);
	~StartGameAnimationController(void);

	virtual void onEnterTransitionDidFinish(); 

private:

	StartGameMenuController *_startGameMenuController;
	cocos2d::Node *_beaver;

	cocos2d::FiniteTimeAction* getAnimationWithMenu();
	cocos2d::FiniteTimeAction* getAnimationWithBeaver();

};

