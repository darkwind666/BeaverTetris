#include "StartGameSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "StartGameAnimationController.h"
#include "RegulateSoundPopUp.h"
#include "StartGameBackgroundController.h"
#include "StartGameFishesController.h"
#include "BackButtonController.h"

using namespace cocos2d;

StartGameSceneFactory::StartGameSceneFactory(void)
{
}


StartGameSceneFactory::~StartGameSceneFactory(void)
{
}

Scene* StartGameSceneFactory::createScene()
{
	Scene *startGameScene = Scene::create();

	StartGameBackgroundController *startGameBackgroundController = new StartGameBackgroundController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(startGameBackgroundController,startGameScene,startGameMenuBackgroundKey);

	StartGameFishesController *startGameFishesController = new StartGameFishesController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(startGameFishesController,startGameScene,startGameFishesKey);

	StartGameAnimationController *startGameAnimationController = new StartGameAnimationController();
	startGameScene->addChild(startGameAnimationController);

	RegulateSoundPopUp *regulateSoundPopUp = new RegulateSoundPopUp();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(regulateSoundPopUp,startGameScene,startGameRegulateSoundPopUpKey);

	BackButtonController *backButtonController = new BackButtonController(kStartGame);
	startGameScene->addChild(backButtonController);

	return startGameScene;
}