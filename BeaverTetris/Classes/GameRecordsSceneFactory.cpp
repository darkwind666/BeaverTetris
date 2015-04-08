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

Scene* GameRecordsSceneFactory::createScene()
{
	Scene *gameRecordsScene = Scene::create();

	LayerColor *background = LayerColor::create(Color4B::MAGENTA);
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