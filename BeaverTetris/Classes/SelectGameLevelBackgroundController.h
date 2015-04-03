#pragma once

#include "cocos2d.h"

class SelectGameLevelBackgroundController : public cocos2d::Node
{
public:
	SelectGameLevelBackgroundController(void);
	~SelectGameLevelBackgroundController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

};

