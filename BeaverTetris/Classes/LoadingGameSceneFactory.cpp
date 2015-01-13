#include "LoadingGameSceneFactory.h"
#include "LoadGameController.h"

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

	CCSprite *beaver = CCSprite::create("HelloWorld.png");
	beaver->setScale(0.3f);
	beaver->setPosition(130, 200);

	LoadGameController *loadGameController = new LoadGameController();
	loadGameController->setPosition(150, 300);

	loadingScene->addChild(background, 1);
	loadingScene->addChild(beaver, 1);
	loadingScene->addChild(loadGameController, 1);

	return loadingScene;

}