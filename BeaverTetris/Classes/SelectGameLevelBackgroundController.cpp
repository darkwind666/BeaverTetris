#include "SelectGameLevelBackgroundController.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"

using namespace cocos2d;

SelectGameLevelBackgroundController::SelectGameLevelBackgroundController(void)
{
	LayerColor *background = LayerColor::create(Color4B::BLUE);
	this->addChild(background);
}


SelectGameLevelBackgroundController::~SelectGameLevelBackgroundController(void)
{
}

void SelectGameLevelBackgroundController::onEnterTransitionDidFinish()
{
	string birdSoundEffect = GameFileExtensionMaker::getSoundWithExtension(birdInForestSoundKey);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(birdSoundEffect);
}

void SelectGameLevelBackgroundController::onExitTransitionDidStart()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}
