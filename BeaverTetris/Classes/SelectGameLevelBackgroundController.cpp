#include "SelectGameLevelBackgroundController.h"
#include "SimpleAudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->playBackgroundMusic(birdSoundEffect.c_str(), true);
}

void SelectGameLevelBackgroundController::onExitTransitionDidStart()
{
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->stopBackgroundMusic();
}
