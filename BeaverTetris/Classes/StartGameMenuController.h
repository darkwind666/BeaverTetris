#pragma once

#include "cocos2d.h"

class StartGameMenuDataSource;

class StartGameMenuController : public cocos2d::Node
{
public:
	StartGameMenuController(void);
	~StartGameMenuController(void);

private :

	StartGameMenuDataSource *_startGameViewDataSource;

	void createStartMenu();
	void buttonWasPressed(cocos2d::Object* pSender);

};

