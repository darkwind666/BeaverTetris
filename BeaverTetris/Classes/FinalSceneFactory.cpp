#include "FinalSceneFactory.h"
#include "CocosNodesHelper.h"
#include "GameStatesHelper.h"
#include "GameViewStyleHelper.h"
#include "GameEnums.h"
#include "GameViewElementsKeys.h"
#include "FinalSceneBackgroundController.h"
#include "FinalSceneAnimationController.h"
#include "BackButtonController.h"
#include "GameLocalizationKeys.h"

using namespace cocos2d;

FinalSceneFactory::FinalSceneFactory(void)
{
}


FinalSceneFactory::~FinalSceneFactory(void)
{
}

Scene* FinalSceneFactory::createScene()
{
	Scene *finalScene = Scene::create();

	FinalSceneBackgroundController *finalSceneBackgroundController = new FinalSceneBackgroundController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(finalSceneBackgroundController, finalScene,  finalScreenBackgroundKey);

	BackButtonController *backButtonController = new BackButtonController(kRecords);
	finalScene->addChild(backButtonController);

	FinalSceneAnimationController *finalSceneAnimationController = new FinalSceneAnimationController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(finalSceneAnimationController, finalScene,  finalScreenAnimationControllerKey);

	std::function<void(Object* pSender)> callback = [](Object* pSender){ 
		Node *button = (Node*)pSender;
		std::function<void()> buttonCallback = [](){GameStatesHelper::goToScene(kRecords);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
	};
	GameViewStyleHelper::addBackButtonToParentNodeWithKeyAndCallbackAndLocalization(finalScene, finalScreenGoToRecordsButtonKey, callback, gameRecordsLocalizationKey);

	return finalScene;
}
