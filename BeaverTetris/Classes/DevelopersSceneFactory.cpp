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

CCScene* DevelopersSceneFactory::createScene()
{
	CCScene *gameDevelopersScene = CCScene::create();

	CCLayerColor *background = CCLayerColor::create(Color4B::GRAY);
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
	std::function<void(CCObject* pSender)> callback = [](CCObject* pSender){ 
		CCNode *button = (CCNode*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kStartGame);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};
	
	CCMenuItemImage *closeButtonItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png",callback);
	closeButtonItem->setColor(ccColor3B::ORANGE);
	closeButtonItem->setScaleX(0.2f);
	closeButtonItem->setScaleY(0.07f);
	return closeButtonItem;
}