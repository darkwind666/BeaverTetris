#pragma once

#include "cocos2d.h"

class GameTimeStepController;
class WinGameSystem;

class MainGamePauseViewController : public cocos2d::Node
{
public:
	MainGamePauseViewController(void);
	~MainGamePauseViewController(void);

	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);

private:

	GameTimeStepController *_gameTimeStepController;
	cocos2d::Node *_pauseView;
	WinGameSystem *_winGameSystem;

	void setPauseView();
	void setUpKeyboard();

};

