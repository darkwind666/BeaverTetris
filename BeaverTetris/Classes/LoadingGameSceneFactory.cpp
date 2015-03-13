#include "LoadingGameSceneFactory.h"
#include "LoadGameController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

LoadingGameSceneFactory::LoadingGameSceneFactory(void)
{
}


LoadingGameSceneFactory::~LoadingGameSceneFactory(void)
{
}

CCScene* LoadingGameSceneFactory::createScene()
{
	CCScene *loadingScene = CCScene::create();

	CCLayerColor *background = CCLayerColor::create(Color4B::RED);
	background->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background,loadingScene,loadingGameBackgroundKey);

	CCNode *beaver = getBeaverWithClock();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaver,loadingScene,loadingGameBeaverKey);

	return loadingScene;
}

CCNode* LoadingGameSceneFactory::getBeaverWithClock()
{
	CCSprite *beaver = CCSprite::create("HelloWorld.png");
	beaver->setScale(0.3f);
	
	LoadGameController *loadGameController = new LoadGameController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(loadGameController,beaver,loadingGameClockKey);
	return beaver;
}

