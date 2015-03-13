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
	cocos2d::Node *_gamesDevelopersBeaver;

	cocos2d::Node* getGameDevelopersBeaver();
	cocos2d::CCFiniteTimeAction* getAnimationWithBoard();
	cocos2d::CCFiniteTimeAction* getAnimationWithBeaver();

};

