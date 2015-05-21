#include "MainGameSceneFactory.h"
#include "GameLogicLoader.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "GameWorldController.h"
#include "GameHudsController.h"
#include "GameTutorialController.h"
#include "MainGamePausePopUp.h"
#include "MainGameEndPopUp.h"
#include "BackButtonController.h"

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
	delete gameLogicLoader;

	Scene *mainGameScene = Scene::create();

	GameWorldController *gameWorldController = new GameWorldController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameWorldController, mainGameScene, gameWorldControllerKey);

	GameHudsController *gameHudsController = new GameHudsController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameHudsController, mainGameScene, gameHudControllerKey);

	MainGamePausePopUp *mainGamePausePopUp = new MainGamePausePopUp(gameWorldController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(mainGamePausePopUp, mainGameScene, mainGamePausePopUpKey);

	MainGameEndPopUp *mainGameEndPopUp = new MainGameEndPopUp(gameWorldController, gameHudsController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(mainGameEndPopUp, mainGameScene, mainGameEndPopUpKey);

	GameTutorialController *gameTutorialController = new GameTutorialController(gameWorldController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameTutorialController, mainGameScene, gameTutorialControllerKey);

	BackButtonController *backButtonController = new BackButtonController(kPlayGame);
	mainGameScene->addChild(backButtonController);

	return mainGameScene;
}