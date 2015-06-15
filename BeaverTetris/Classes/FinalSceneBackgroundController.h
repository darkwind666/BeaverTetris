#pragma once

#include "cocos2d.h"

class FinalSceneBackgroundController : public cocos2d::Node
{
public:
	FinalSceneBackgroundController(void);
	~FinalSceneBackgroundController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

};

