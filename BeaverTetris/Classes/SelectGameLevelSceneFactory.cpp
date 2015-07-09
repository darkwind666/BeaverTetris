#include "SelectGameLevelSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "SelectGameLevelController.h"
#include "SelectLevelPlayerStatusController.h"
#include "PlayerCreatorController.h"
#include "SelectGameLevelBeaverTalkController.h"
#include "GameViewStyleHelper.h"
#include "BackButtonController.h"

using namespace cocos2d;

SelectGameLevelSceneFactory::SelectGameLevelSceneFactory(void)
{
}


SelectGameLevelSceneFactory::~SelectGameLevelSceneFactory(void)
{
}

Scene* SelectGameLevelSceneFactory::createScene()
{
	Scene *selectGameLevelScene = Scene::create();

	
	SelectGameLevelBeaverTalkController *selectGameLevelBeaverTalkController = new SelectGameLevelBeaverTalkController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(selectGameLevelBeaverTalkController,selectGameLevelScene,selectLevelBeaverTalkKey);

	SelectGameLevelController *selectGameLevelController = new SelectGameLevelController();
	selectGameLevelController->setDelegate(selectGameLevelBeaverTalkController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(selectGameLevelController,selectGameLevelScene,selectLevelMenuKey);
	
	SelectLevelPlayerStatusController *selectLevelPlayerStatusController = new SelectLevelPlayerStatusController();
	selectLevelPlayerStatusController->setDelegate(selectGameLevelController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(selectLevelPlayerStatusController,selectGameLevelScene,selectLevelScenePlayerStatusControllerKey);

	PlayerCreatorController *playerCreatorController = new PlayerCreatorController();
	playerCreatorController->setDelegate(selectLevelPlayerStatusController);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(playerCreatorController,selectGameLevelScene,playerCreatorControllerKey);
	GameViewStyleHelper::addBackButtonToParentNodeWithKey(selectGameLevelScene, selectLevelSceneBackButtonKey);

	BackButtonController *backButtonController = new BackButtonController(kSelectLevel);
	selectGameLevelScene->addChild(backButtonController);

	return selectGameLevelScene;
}