#pragma once

#include "PlayerStatusDelegateInterface.h"
#include "cocos2d.h"

class SelectGameLevelBeaverTalkController : public cocos2d::Node, public PlayerStatusDelegateInterface
{
public:
	SelectGameLevelBeaverTalkController(void);
	~SelectGameLevelBeaverTalkController(void);

	virtual void showPlayerStatus();

};

