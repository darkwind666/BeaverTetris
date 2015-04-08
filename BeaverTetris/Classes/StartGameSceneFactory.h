#pragma once

#include "SceneFactory.h"

class StartGameSceneFactory : public SceneFactory
{
public:
	StartGameSceneFactory(void);
	~StartGameSceneFactory(void);

	virtual cocos2d::Scene* createScene();

};

