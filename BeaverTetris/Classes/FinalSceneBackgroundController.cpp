#include "FinalSceneBackgroundController.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

FinalSceneBackgroundController::FinalSceneBackgroundController(void)
{
	Sprite *background = CocosNodesHelper::getSpriteWithKey(finalScreenBackgroundKey);
	this->addChild(background);
}


FinalSceneBackgroundController::~FinalSceneBackgroundController(void)
{
}

void FinalSceneBackgroundController::onEnterTransitionDidFinish()
{
	string waterSoundEffect = GameFileExtensionMaker::getSoundWithExtension(winAllGameSoundKey);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(waterSoundEffect);
}

void FinalSceneBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}
