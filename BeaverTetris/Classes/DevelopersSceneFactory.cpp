#include "DevelopersSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"
#include "GameViewElementsKeys.h"
#include "GamesDevelopersAnimationController.h"
#include "StartGameFishesController.h"

using namespace cocos2d;

DevelopersSceneFactory::DevelopersSceneFactory(void)
{
}


DevelopersSceneFactory::~DevelopersSceneFactory(void)
{
}

Scene* DevelopersSceneFactory::createScene()
{
	Scene *gameDevelopersScene = Scene::create();

	CocosNodesHelper::addSpriteToParentNodeWithKey(gameDevelopersScene, gameDevelopersBackgroundKey);
	CocosNodesHelper::addSpriteToParentNodeWithKey(gameDevelopersScene, gameDevelopersUnderWaterBackgroundKey);

	StartGameFishesController *startGameFishesController = new StartGameFishesController();
	startGameFishesController->setFirstFishScale(0.5f);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(startGameFishesController,gameDevelopersScene,gameDevelopersFishesKey);

	GamesDevelopersAnimationController *developersAnimationController = new GamesDevelopersAnimationController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(developersAnimationController,gameDevelopersScene,gameDevelopersAnimationControllerKey);

	return gameDevelopersScene;
}