#pragma once

#include "cocos2d.h"

class GameHudsController : public cocos2d::Node
{
public:
	GameHudsController(void);
	~GameHudsController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);

	void pauseHuds();
	void resumeHuds();

private:

	cocos2d::Node *_playerScoreController;
	cocos2d::Node *_victoryConditionController;
	cocos2d::Node *_playerSpellsController;

	void makeView();

};

