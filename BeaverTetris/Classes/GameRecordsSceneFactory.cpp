#include "GameRecordsSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"
#include "GameViewElementsKeys.h"
#include "GamesRecordsAnimationController.h"

using namespace cocos2d;

GameRecordsSceneFactory::GameRecordsSceneFactory(void)
{
}


GameRecordsSceneFactory::~GameRecordsSceneFactory(void)
{
}

CCScene* GameRecordsSceneFactory::createScene()
{
	CCScene *gameRecordsScene = CCScene::create();

	CCLayerColor *background = CCLayerColor::create(Color4B::MAGENTA);
	background->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background,gameRecordsScene,gameRecordsBackgroundKey);

	GamesRecordsAnimationController *gamesRecordsAnimationController = new GamesRecordsAnimationController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gamesRecordsAnimationController,gameRecordsScene,gameRecordsAnimationControllerKey);

	MenuItemImage *goToMainMenuButton = getCloseButton();
	CocosNodesHelper::addButtonToParentNodeWithKey(goToMainMenuButton,gameRecordsScene,gameRecordsGoToMainMenuButtonKey);

	return gameRecordsScene;
}

MenuItemImage* GameRecordsSceneFactory::getCloseButton()
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