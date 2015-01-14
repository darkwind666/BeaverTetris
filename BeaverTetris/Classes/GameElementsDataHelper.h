#pragma once

#include "cocos2d.h"

class GameElementsDataHelper
{
public:
	GameElementsDataHelper(void);
	~GameElementsDataHelper(void);

	static cocos2d::Vec2 getElementOffsetForKey(std::string aKey);
	static cocos2d::Vec2 getElementFinalActionPositionForKey(std::string aKey);

};

