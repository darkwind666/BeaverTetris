#include "SceneFactory.h"
#include "cocos2d.h"

using namespace cocos2d;

SceneFactory::SceneFactory(void)
{
}


SceneFactory::~SceneFactory(void)
{
}

CCScene* SceneFactory::createScene()
{
	CCScene *defaultScene = CCScene::create();
	return defaultScene;
}