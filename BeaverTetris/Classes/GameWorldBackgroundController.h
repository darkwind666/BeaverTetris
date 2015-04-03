#pragma once

#include "cocos2d.h"
#include <string>

class MainGameBackgroundDataSource;

class GameWorldBackgroundController : public cocos2d::Node
{
public:
	GameWorldBackgroundController(void);
	~GameWorldBackgroundController(void);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

private:

	MainGameBackgroundDataSource *_mainGameBackgroundDataSource;

	void makeControllerView();
	std::string getMainGameBackgroundMusicName();

};

