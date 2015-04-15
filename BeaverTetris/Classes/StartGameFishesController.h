#pragma once

#include "cocos2d.h"

class StartGameFishesController : public cocos2d::Node
{
public:
	StartGameFishesController(void);
	~StartGameFishesController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

private:

	cocos2d::Node *_fish1;
	cocos2d::Node *_fish2;
	cocos2d::Node *_fish3;

	void runFish1Animation();
	void runFish2Animation();
	void runFish3Animation();

};

