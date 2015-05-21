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

	void setUpKeyboard();
	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);
	cocos2d::ActionInterval* getBeaverAnimation();
	cocos2d::ActionInterval* getNextTutorialBeaverAnimation();

};

