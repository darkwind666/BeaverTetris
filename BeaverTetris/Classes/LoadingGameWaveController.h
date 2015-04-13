#pragma once

#include "cocos2d.h"

class LoadingGameWaveController : public cocos2d::Node
{
public:
	LoadingGameWaveController(void);
	~LoadingGameWaveController(void);

	virtual void onEnterTransitionDidFinish(); 
	virtual void onExitTransitionDidStart();

private:

	void makeWavesView();
	cocos2d::Action* getWavesAction();

};

