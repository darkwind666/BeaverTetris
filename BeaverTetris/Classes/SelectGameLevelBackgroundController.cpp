#include "SelectGameLevelBackgroundController.h"
#include "AudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace cocos2d;
using namespace experimental;

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
	AudioEngine::play2d(birdSoundEffect, true);
}

void SelectGameLevelBackgroundController::onExitTransitionDidStart()
{
	AudioEngine::stopAll();
}
