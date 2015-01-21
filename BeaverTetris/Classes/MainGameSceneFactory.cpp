#include "MainGameSceneFactory.h"
#include "GameLogicLoader.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "GameWorldController.h"

using namespace cocos2d;

MainGameSceneFactory::MainGameSceneFactory(void)
{
}


MainGameSceneFactory::~MainGameSceneFactory(void)
{
}

Scene* createScene()
{
	GameLogicLoader *gameLogicLoader = new GameLogicLoader();
	gameLogicLoader->loadResources();

	Scene *mainGameScene = Scene::create();

	GameWorldController *gameWorldController = new GameWorldController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameWorldController, mainGameScene, gameWorldControllerKey);

	return mainGameScene;
}