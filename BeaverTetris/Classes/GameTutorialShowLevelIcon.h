#pragma once

#include "cocos2d.h"

class GameTutorialShowLevelIcon : public cocos2d::Node
{
public:
	GameTutorialShowLevelIcon(void);
	~GameTutorialShowLevelIcon(void);

	virtual void onExitTransitionDidStart();

	void showIcon();

private:

	cocos2d::Node *_currentLevelMark;
	bool _showMark;

};

