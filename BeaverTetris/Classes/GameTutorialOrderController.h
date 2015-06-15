#pragma once

#include "cocos2d.h"

class GameTutorial;

class GameTutorialOrderController : public cocos2d::Node
{
public:
	GameTutorialOrderController(GameTutorial *aGameTutorial);
	~GameTutorialOrderController(void);

	void startTutorial();

private:

	GameTutorial *_gameTutorial;
	bool _availableTutorials;
	cocos2d::Node *_tutorialBeaver;
	cocos2d::Vec2 _startBeaverPosition;
	bool _beaverAnimationFinished;
	cocos2d::EventListenerTouchOneByOne *_listner;

	void setUpKeyboard();
	cocos2d::EventListenerTouchOneByOne* getListner();
	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);
	void nextTutorial();
	cocos2d::ActionInterval* getBeaverAnimation();
	cocos2d::ActionInterval* getNextTutorialBeaverAnimation();

};

