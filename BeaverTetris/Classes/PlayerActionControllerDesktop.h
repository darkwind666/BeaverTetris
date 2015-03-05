#pragma once

#include "cocos2d.h"
#include <map>
#include <functional>

class PlayerGameControlsDataSource;
class GameTimeStepController;

class PlayerActionControllerDesktop : public cocos2d::Node
{
public:
	PlayerActionControllerDesktop(void);
	~PlayerActionControllerDesktop(void);

	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);

private:

	PlayerGameControlsDataSource *_playerGameControlsDataSource;
	GameTimeStepController *_gameTimeStepController;
	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> _controllersViews;

	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> makeControllersViews();
	void setUpKeyboard();
	void addViewsToController(std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::Node*> aViews);
	std::function<void()> getCallbackWithButtonIndex(int aButtonIndex);
};

