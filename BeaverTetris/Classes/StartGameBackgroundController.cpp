#include "StartGameBackgroundController.h"
#include "SimpleAudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->playBackgroundMusic(waterSoundEffect.c_str(), true);
}

void StartGameBackgroundController::onExitTransitionDidStart()
{
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->stopBackgroundMusic();
}

