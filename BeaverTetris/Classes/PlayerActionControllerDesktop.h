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
	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::MenuItem*> _controllersViews;

	std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::MenuItem*> makeControllersViews();
	cocos2d::MenuItem* getPlayerControlView();
	void setUpKeyboard();
	void addViewsToController(std::map<cocos2d::EventKeyboard::KeyCode, cocos2d::MenuItem*> aViews);
	void activatePlayerControllerOnKeyCode(cocos2d::EventKeyboard::KeyCode aKeyCode);
	std::function<void()> getCallbackWithButtonIndex(int aButtonIndex);
};

