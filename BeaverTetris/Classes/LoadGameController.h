#pragma once

#include "cocos2d.h"

class LoadGameController : public cocos2d::CCNode
{
public:
	LoadGameController(void);
	~LoadGameController(void);

	virtual void update(float delta);
	virtual void onEnterTransitionDidFinish(); 

private:

	cocos2d::CCProgressTimer *_loadGameControllerView;

};

