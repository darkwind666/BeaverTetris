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

	void setMouseListner();
	std::vector<cocos2d::Node*> getMenuItems();
	void makeStartMenuView();
	void createStartMenu();
	void onMouseMove(cocos2d::Event *aEvent);
	void configurateMenuItemsWithMouseLocation(cocos2d::Vec2 aMouseLocation);
	void changeMenuItemImageWithMouseLocation(cocos2d::MenuItem *aMenuItem, cocos2d::Vec2 aMouseLocation);
	void buttonWasPressed(cocos2d::Object* pSender);

};

