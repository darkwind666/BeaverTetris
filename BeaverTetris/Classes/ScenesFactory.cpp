#include "ScenesFactory.h"
#include "SceneFactory.h"

#include "LoadingGameSceneFactory.h"
#include "StartGameSceneFactory.h"
#include "SelectGameLevelSceneFactory.h"
#include "MainGameSceneFactory.h"
#include "GameRecordsSceneFactory.h"
#include "DevelopersSceneFactory.h"

using namespace std;
using namespace cocos2d;

ScenesFactory::ScenesFactory(void)
{
	_scenesFactories = getScenesFactories();
}


ScenesFactory::~ScenesFactory(void)
{
}

Scene* ScenesFactory::getGameSceneForId(GameState aSceneId)
{
	SceneFactory *sceneFactory = _scenesFactories[aSceneId];
	return sceneFactory->createScene();
}

std::map<GameState, SceneFactory*> ScenesFactory::getScenesFactories()
{
	map<GameState, SceneFactory*> scenesFactories;

	scenesFactories[kLoadGame] = new LoadingGameSceneFactory();
	scenesFactories[kStartGame] = new StartGameSceneFactory();
	scenesFactories[kSelectLevel] = new SelectGameLevelSceneFactory();
	scenesFactories[kPlayGame] = new MainGameSceneFactory();
	scenesFactories[kRecords] = new GameRecordsSceneFactory();
	scenesFactories[kDevelopers] = new DevelopersSceneFactory();

	return scenesFactories;
}



