#pragma once

#include "SceneFactory.h"
#include "cocos2d.h"

class MainGameSceneFactory : public SceneFactory
{
public:
	MainGameSceneFactory(void);
	~MainGameSceneFactory(void);

	virtual cocos2d::Scene* createScene();

};

