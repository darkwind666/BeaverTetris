#include "StartGameSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "StartGameAnimationController.h"

using namespace cocos2d;

StartGameSceneFactory::StartGameSceneFactory(void)
{
}


StartGameSceneFactory::~StartGameSceneFactory(void)
{
}

CCScene* StartGameSceneFactory::createScene()
{
	CCScene *startGameScene = CCScene::create();

	CCLayerColor *background = CCLayerColor::create(Color4B::GREEN);
	background->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background,startGameScene,startGameMenuBackgroundKey);

	StartGameAnimationController *startGameAnimationController = new StartGameAnimationController();
	startGameScene->addChild(startGameAnimationController);

	return startGameScene;
}