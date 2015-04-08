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

Scene* LoadingGameSceneFactory::createScene()
{
	Scene *loadingScene = Scene::create();

	LayerColor *background = LayerColor::create(Color4B::RED);
	background->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(background,loadingScene,loadingGameBackgroundKey);

	Node *beaver = getBeaverWithClock();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaver,loadingScene,loadingGameBeaverKey);

	return loadingScene;
}

Node* LoadingGameSceneFactory::getBeaverWithClock()
{
	Sprite *beaver = Sprite::create("HelloWorld.png");
	beaver->setScale(0.3f);
	
	LoadGameController *loadGameController = new LoadGameController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(loadGameController,beaver,loadingGameClockKey);
	return beaver;
}

