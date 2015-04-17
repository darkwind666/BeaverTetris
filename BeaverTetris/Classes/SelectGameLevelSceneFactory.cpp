#include "SelectGameLevelSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "SelectGameLevelController.h"
#include "SelectLevelPlayerStatusController.h"
#include "PlayerCreatorController.h"
#include "SelectGameLevelBeaverTalkController.h"
#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"

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

	MenuItemImage *closeButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButton,selectGameLevelScene,selectLevelSceneBackButtonKey);

	return selectGameLevelScene;
}

MenuItemImage* SelectGameLevelSceneFactory::getCloseButton()
{
	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};
	
	MenuItemImage *closeButtonItem = MenuItemImage::create("HelloWorld.png","HelloWorld.png",callback);
	closeButtonItem->setColor(Color3B::ORANGE);
	closeButtonItem->setScaleX(0.2f);
	closeButtonItem->setScaleY(0.07f);
	return closeButtonItem;
}