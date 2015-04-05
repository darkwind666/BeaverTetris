#pragma once

#include "SceneFactory.h"
#include "cocos2d.h"

class GameRecordsSceneFactory : public SceneFactory
{
public:
	GameRecordsSceneFactory(void);
	~GameRecordsSceneFactory(void);

	virtual cocos2d::CCScene* createScene();

private:

	cocos2d::MenuItemImage* getCloseButton();

};
