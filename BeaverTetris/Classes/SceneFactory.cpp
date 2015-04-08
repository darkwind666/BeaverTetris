#include "SceneFactory.h"
#include "cocos2d.h"

using namespace cocos2d;

SceneFactory::SceneFactory(void)
{
}


SceneFactory::~SceneFactory(void)
{
}

Scene* SceneFactory::createScene()
{
	Scene *defaultScene = Scene::create();
	return defaultScene;
}