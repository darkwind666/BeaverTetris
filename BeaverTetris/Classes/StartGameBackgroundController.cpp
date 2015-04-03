#include "StartGameBackgroundController.h"
#include "AudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace cocos2d;
using namespace experimental;

StartGameBackgroundController::StartGameBackgroundController(void)
{
	LayerColor *background = LayerColor::create(Color4B::GREEN);
	background->ignoreAnchorPointForPosition(false);
	this->addChild(background);
}


StartGameBackgroundController::~StartGameBackgroundController(void)
{
}

void StartGameBackgroundController::onEnterTransitionDidFinish()
{
	string waterSoundEffect = GameFileExtensionMaker::getSoundWithExtension(waterSoundKey);
	AudioEngine::play2d(waterSoundEffect, true);
}

void StartGameBackgroundController::onExitTransitionDidStart()
{
	AudioEngine::stopAll();
}

