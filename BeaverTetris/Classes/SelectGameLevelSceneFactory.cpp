#include "SelectGameLevelSceneFactory.h"
#include "SelectGameLevelController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

SelectGameLevelSceneFactory::SelectGameLevelSceneFactory(void)
{
}


SelectGameLevelSceneFactory::~SelectGameLevelSceneFactory(void)
{
}

CCScene* SelectGameLevelSceneFactory::createScene()
{
	CCScene *selectGameLevelScene = CCScene::create();

	SelectGameLevelController *selectGameLevelController = new SelectGameLevelController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(selectGameLevelController,selectGameLevelScene,selectLevelMenuKey);


	return selectGameLevelScene;
}