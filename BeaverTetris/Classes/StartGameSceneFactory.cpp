#include "StartGameSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "StartGameAnimationController.h"
#include "RegulateSoundPopUp.h"
#include "StartGameBackgroundController.h"

using namespace cocos2d;

StartGameSceneFactory::StartGameSceneFactory(void)
{
}


StartGameSceneFactory::~StartGameSceneFactory(void)
{
}

CCScene* StartGameSceneFactory::createScene()
{
	CCScene *startGameScene = CCScene::create();

	StartGameBackgroundController *startGameBackgroundController = new StartGameBackgroundController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(startGameBackgroundController,startGameScene,startGameMenuBackgroundKey);

	StartGameAnimationController *startGameAnimationController = new StartGameAnimationController();
	startGameScene->addChild(startGameAnimationController);

	RegulateSoundPopUp *regulateSoundPopUp = new RegulateSoundPopUp();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(regulateSoundPopUp,startGameScene,startGameRegulateSoundPopUpKey);

	return startGameScene;
}