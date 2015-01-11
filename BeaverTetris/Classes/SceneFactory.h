#pragma once

#include "cocos2d.h"

class SceneFactory
{
public:
	SceneFactory(void);
	virtual ~SceneFactory(void);

	virtual cocos2d::CCScene* createScene() = 0;

};

