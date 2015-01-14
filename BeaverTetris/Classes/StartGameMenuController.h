#pragma once

#include "cocos2d.h"

class StartGameMenuDataSource;

class StartGameMenuController : public cocos2d::CCNode
{
public:
	StartGameMenuController(void);
	~StartGameMenuController(void);

private :

	StartGameMenuDataSource *_startGameViewDataSource;

	void createStartMenu();
	void buttonWasPressed(cocos2d::CCObject* pSender);

};

