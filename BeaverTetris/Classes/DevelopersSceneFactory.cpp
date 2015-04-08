#include "DevelopersSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"
#include "GameViewElementsKeys.h"
#include "GamesDevelopersAnimationController.h"

using namespace cocos2d;

DevelopersSceneFactory::DevelopersSceneFactory(void)
{
}


DevelopersSceneFactory::~DevelopersSceneFactory(void)
{
}

Scene* DevelopersSceneFactory::createScene()
{
	Scene *gameDevelopersScene = Scene::create();

	LayerColor *background = LayerColor::create(Color4B::GRAY);
	background->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background,gameDevelopersScene,gameDevelopersBackgroundKey);

	GamesDevelopersAnimationController *developersAnimationController = new GamesDevelopersAnimationController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developersAnimationController,gameDevelopersScene,gameDevelopersAnimationControllerKey);

	MenuItemImage *goToMainMenuButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(goToMainMenuButton,gameDevelopersScene,gameDevelopersGoToMainMenuButtonKey);

	return gameDevelopersScene;
}

MenuItemImage* DevelopersSceneFactory::getCloseButton()
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