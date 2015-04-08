#pragma once

#include "SceneFactory.h"
#include "cocos2d.h"

class LoadingGameSceneFactory : public SceneFactory
{
public:
	LoadingGameSceneFactory(void);
	~LoadingGameSceneFactory(void);

	virtual cocos2d::Scene* createScene();

private:

	cocos2d::Node* getBeaverWithClock();

};

