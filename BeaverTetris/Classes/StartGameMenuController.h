#pragma once

#include "cocos2d.h"
#include <vector>

class StartGameMenuDataSource;

class StartGameMenuController : public cocos2d::Node
{
public:
	StartGameMenuController(void);
	~StartGameMenuController(void);

private :

	StartGameMenuDataSource *_startGameViewDataSource;
	std::vector<cocos2d::Node*> _menuItems;

	std::vector<cocos2d::Node*> getMenuItems();
	cocos2d::Node* getButtonTextForIndex(int aIndex);
	void makeStartMenuView();
	void createStartMenu();
	void buttonWasPressed(cocos2d::Object* pSender);

};

