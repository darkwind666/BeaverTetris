#include "StartGameBackgroundController.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

StartGameBackgroundController::StartGameBackgroundController(void)
{
	Sprite *background = CocosNodesHelper::getSpriteWithKey(startGameMenuBackgroundKey);
	this->addChild(background);
}


StartGameBackgroundController::~StartGameBackgroundController(void)
{
}

void StartGameBackgroundController::onEnterTransitionDidFinish()
{
	string waterSoundEffect = GameFileExtensionMaker::getSoundWithExtension(waterSoundKey);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(waterSoundEffect);
}

void StartGameBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}
