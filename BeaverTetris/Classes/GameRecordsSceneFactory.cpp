#include "GameRecordsSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameViewElementsKeys.h"
#include "GamesRecordsAnimationController.h"
#include "GameRecordsFishesController.h"
#include "BackButtonController.h"

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

	CocosNodesHelper::addSpriteToParentNodeWithKey(gameRecordsScene, gameRecordsBackgroundKey);
	CocosNodesHelper::addSpriteToParentNodeWithKey(gameRecordsScene, gameRecordsUnderWaterBackgroundKey);

	GamesRecordsAnimationController *gamesRecordsAnimationController = new GamesRecordsAnimationController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gamesRecordsAnimationController,gameRecordsScene,gameRecordsAnimationControllerKey);

	GameRecordsFishesController *gameRecordsFishesController = new GameRecordsFishesController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(gameRecordsFishesController,gameRecordsScene,gameRecordsFishesKey);

	BackButtonController *backButtonController = new BackButtonController(kRecords);
	gameRecordsScene->addChild(backButtonController);

	return gameRecordsScene;
}