#pragma once

#include "SceneFactory.h"
#include "cocos2d.h"

class FinalSceneFactory : public SceneFactory
{
public:
	FinalSceneFactory(void);
	~FinalSceneFactory(void);

	virtual cocos2d::Scene* createScene();

};

