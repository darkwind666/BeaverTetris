#pragma once

#include "cocos2d.h"

class GameRecordsFishesController : public cocos2d::Node
{
public:
	GameRecordsFishesController(void);
	~GameRecordsFishesController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	private:

	cocos2d::Node *_fish1;
	cocos2d::Node *_fish2;

	void runFish1Animation();
	void runFish2Animation();

};

