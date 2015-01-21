#pragma once

#include "cocos2d.h"

class GameWorldController : public cocos2d::Node
{
public:
	GameWorldController(void);
	~GameWorldController(void);

private:

	void makeControllerView();

};

