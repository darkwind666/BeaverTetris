#include "SelectGameLevelSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "SelectGameLevelController.h"
#include "SelectLevelPlayerStatusController.h"

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

	SelectLevelPlayerStatusController *selectLevelPlayerStatusController = new SelectLevelPlayerStatusController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(selectLevelPlayerStatusController,selectGameLevelScene,selectLevelScenePlayerStatusControllerKey);

	return selectGameLevelScene;
}