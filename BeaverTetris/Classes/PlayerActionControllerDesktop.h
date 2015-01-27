#pragma once

#include "cocos2d.h"
#include <map>

class PlayerGameControlsDataSource;

class PlayerActionControllerDesktop : public cocos2d::Node
{
public:
	PlayerActionControllerDesktop(void);
	~PlayerActionControllerDesktop(void);

	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);

private:

	PlayerGameControlsDataSource *_playerGameControlsDataSource;
	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> _controllersViews;

	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> makeControllersViews();
	void setUpKeyboard();
	void addViewsToController(std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> aViews);

};

