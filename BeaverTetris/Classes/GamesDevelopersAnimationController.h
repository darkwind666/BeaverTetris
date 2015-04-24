#pragma once

#include "cocos2d.h"

class GamesDevelopersAnimationController : public cocos2d::Node
{
public:
	GamesDevelopersAnimationController(void);
	~GamesDevelopersAnimationController(void);

	virtual void onEnterTransitionDidFinish();

private:

	cocos2d::Node *_gamesDevelopersBoard;
	cocos2d::Node *_underWaterBoardPart;
	cocos2d::Node *_gamesDevelopersBeaver;

	cocos2d::FiniteTimeAction* getAnimationWithBoard();
	cocos2d::FiniteTimeAction* getAnimationWithBoardUnderWaterPart();
	cocos2d::FiniteTimeAction* getAnimationWithBeaver();

};

