#pragma once

#include "cocos2d.h"
#include "MainGamePauseEndObserver.h"

class GameTimeStepController;
class WinGameSystem;
class EventListenerKeyboard;

class MainGamePauseViewController : public cocos2d::Node, public MainGamePauseEndObserver
{
public:
	MainGamePauseViewController(void);
	~MainGamePauseViewController(void);

	virtual void pauseWasEnded();

	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);

private:

	GameTimeStepController *_gameTimeStepController;
	cocos2d::Node *_pauseView;
	WinGameSystem *_winGameSystem;
	cocos2d::EventListenerKeyboard *_eventListenerKeyboard;

	void setPauseView();
	void setUpKeyboard();

};

