#pragma once

#include "cocos2d.h"

class SelectGameLevelBeaverOnRaftController : public cocos2d::Node
{
public:
	SelectGameLevelBeaverOnRaftController(void);
	~SelectGameLevelBeaverOnRaftController(void);

private:

	cocos2d::Vec2 getPositionForBeaverOnRaft();

};

