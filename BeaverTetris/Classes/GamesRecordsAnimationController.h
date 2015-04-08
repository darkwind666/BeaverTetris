#pragma once

#include "cocos2d.h"

class GamesRecordsAnimationController : public cocos2d::Node
{
public:
	GamesRecordsAnimationController(void);
	~GamesRecordsAnimationController(void);

	virtual void onEnterTransitionDidFinish();

private:

	cocos2d::Node *_gamesRecordsBoard;
	cocos2d::Node *_gamesRecordsBeaver;

	cocos2d::Node* getGameRecordsBeaver();
	cocos2d::FiniteTimeAction* getAnimationWithBoard();
	cocos2d::FiniteTimeAction* getAnimationWithBeaver();

};

