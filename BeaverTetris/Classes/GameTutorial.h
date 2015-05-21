#pragma once

#include "cocos2d.h"

class GameTutorial : public cocos2d::Node
{
public:
	GameTutorial();
	virtual ~GameTutorial(void);

	virtual void startTutorial() = 0;
	virtual void nextTutorial() = 0;
	virtual bool availableTutorials() = 0;

};

