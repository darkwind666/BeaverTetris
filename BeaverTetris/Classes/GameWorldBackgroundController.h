#pragma once

#include "cocos2d.h"

class MainGameBackgroundDataSource;

class GameWorldBackgroundController : public cocos2d::Node
{
public:
	GameWorldBackgroundController(void);
	~GameWorldBackgroundController(void);

private:

	MainGameBackgroundDataSource *_mainGameBackgroundDataSource;

	void makeControllerView();

};

