#pragma once

#include "cocos2d.h"

class CurrentPlayerDataSource;

class MainGamePlayerScoreController : public cocos2d::Node
{
public:
	MainGamePlayerScoreController(void);
	~MainGamePlayerScoreController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void update(float delta);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	cocos2d::LabelTTF *_scoreView;

	void makeControllerView();

};

