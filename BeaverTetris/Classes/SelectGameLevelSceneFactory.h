#pragma once

#include "SceneFactory.h"

class SelectGameLevelSceneFactory : public SceneFactory
{
public:
	SelectGameLevelSceneFactory(void);
	~SelectGameLevelSceneFactory(void);

	virtual cocos2d::CCScene* createScene();

private:

	cocos2d::MenuItemImage* getCloseButton();

};

