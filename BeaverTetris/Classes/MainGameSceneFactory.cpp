#include "MainGameSceneFactory.h"
#include "GameLogicLoader.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "GameWorldController.h"
#include "GameHudsController.h"
#include "MainGamePausePopUp.h"
#include "MainGameEndPopUp.h"

using namespace cocos2d;

MainGameSceneFactory::MainGameSceneFactory(void)
{
}


MainGameSceneFactory::~MainGameSceneFactory(void)
{
}

Scene* MainGameSceneFactory::createScene()
{
	GameLogicLoader *gameLogicLoader = new GameLogicLoader();
	gameLogicLoader->loadResources();

	Scene *mainGameScene = Scene::create();

	GameWorldController *gameWorldController = new GameWorldController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameWorldController, mainGameScene, gameWorldControllerKey);

	GameHudsController *gameHudsController = new GameHudsController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameHudsController, mainGameScene, gameHudControllerKey);

	MainGamePausePopUp *mainGamePausePopUp = new MainGamePausePopUp(gameWorldController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(mainGamePausePopUp, mainGameScene, mainGamePausePopUpKey);

	MainGameEndPopUp *mainGameEndPopUp = new MainGameEndPopUp();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(mainGameEndPopUp, mainGameScene, mainGameEndPopUpKey);

	return mainGameScene;
}