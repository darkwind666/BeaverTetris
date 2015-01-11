#pragma once

#include "GameEnums.h"
#include "cocos2d.h"
#include <map>

class SceneFactory;

class ScenesFactory
{
public:
	ScenesFactory(void);
	~ScenesFactory(void);

	cocos2d::CCScene* getGameSceneForId(GameState aSceneId);

private:

	std::map<GameState, SceneFactory*> _scenesFactories;

	std::map<GameState, SceneFactory*> getScenesFactories();

};

