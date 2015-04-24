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
#include "GameKeyWithSuffixSupporter.h"
#include "MouseOverMenuItem.h"

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

	MenuItem *closeButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(closeButton,selectGameLevelScene,selectLevelSceneBackButtonKey);

	return selectGameLevelScene;
}

MenuItem* SelectGameLevelSceneFactory::getCloseButton()
{
	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};

	string inactiveImageName = GameKeyWithSuffixSupporter::makeUnselectedImageForKey(selectLevelSceneBackButtonKey);
	string activeImageName = GameKeyWithSuffixSupporter::makeSelectedImageForKey(selectLevelSceneBackButtonKey);
	MouseOverMenuItem *closeButtonItem = new MouseOverMenuItem(activeImageName,inactiveImageName,callback);
	return closeButtonItem;
}