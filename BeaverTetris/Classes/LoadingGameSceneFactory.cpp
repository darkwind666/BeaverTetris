#include "LoadingGameSceneFactory.h"
#include "LoadGameController.h"
#include "LoadingGameWaveController.h"
#include "CocosNodesHelper.h"
#include "GameFileExtensionMaker.h"
#include "GameViewElementsKeys.h"
#include "BackButtonController.h"

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
	CocosNodesHelper::addSpriteToParentNodeWithKey(loadingScene, loadingGameBackgroundKey);

	Node *gameName = CocosNodesHelper::getSpriteWithKey(loadingGameNameKey);
	gameName->setScale(0.9f);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameName,loadingScene,loadingGameNameKey);

	Node *beaver = getBeaverWithClock();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(beaver,loadingScene,loadingGameBeaverKey);

	LoadingGameWaveController *wave = new LoadingGameWaveController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(wave,loadingScene,loadingGameWaveKey);

	BackButtonController *backButtonController = new BackButtonController(kLoadGame);
	loadingScene->addChild(backButtonController);

	return loadingScene;
}

Node* LoadingGameSceneFactory::getBeaverWithClock()
{
	Sprite *beaver = CocosNodesHelper::getSpriteWithKey(loadingGameBeaverKey);
	LoadGameController *loadGameController = new LoadGameController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(loadGameController,beaver,loadingGameClockKey);
	return beaver;
}

