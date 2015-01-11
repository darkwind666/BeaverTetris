#pragma once

#include "SceneFactory.h"

class LoadingGameSceneFactory : public SceneFactory
{
public:
	LoadingGameSceneFactory(void);
	~LoadingGameSceneFactory(void);

	virtual cocos2d::CCScene* createScene();

};

