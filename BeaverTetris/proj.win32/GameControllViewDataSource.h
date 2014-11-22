#pragma once

#include <string>
#include "cocos2d.h"

class GameControllViewDataSource
{
public:
	GameControllViewDataSource(void);
	~GameControllViewDataSource(void);

	int getControllElementsCount(void);
	std::string getControllImageForIndex(int aIndex);
	cocos2d::Vec2 getControllPositionForIndex(int aIndex);

};

