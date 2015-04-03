#pragma once

#include "cocos2d.h"

class StartGameBackgroundController : public cocos2d::Node
{
public:
	StartGameBackgroundController(void);
	~StartGameBackgroundController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

};

