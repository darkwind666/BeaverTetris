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

};

