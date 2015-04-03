#include "MainGameEndPopUpSoundController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "SimpleAudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"

using namespace CocosDenshion;
using namespace std;

MainGameEndPopUpSoundController::MainGameEndPopUpSoundController(void)
{
	_winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	_currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
}


MainGameEndPopUpSoundController::~MainGameEndPopUpSoundController(void)
{
}

void MainGameEndPopUpSoundController::playEndGameSound()
{
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->stopBackgroundMusic();
	playGameResultSound();
}

void MainGameEndPopUpSoundController::playGameResultSound()
{
	if (_winGameSystem->playerWin())
	{
		playWinGameSound();
	}
	else
	{
		playSoundWithKey(loseLevelSoundKey);
	}
}

void MainGameEndPopUpSoundController::playWinGameSound()
{
	if (_currentLevelDataSource->finalLevel())
	{
		playSoundWithKey(winAllGameSoundKey);
	}
	else
	{
		playSoundWithKey(winLevelSoundKey);
	}
}

void MainGameEndPopUpSoundController::playSoundWithKey(string aKey)
{
	string loseGameSoundEffect = GameFileExtensionMaker::getSoundWithExtension(aKey);
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->playEffect(loseGameSoundEffect.c_str(), true);
}

void MainGameEndPopUpSoundController::stopPlayingSound()
{
	SimpleAudioEngine *audioEngine = SimpleAudioEngine::sharedEngine();
	audioEngine->stopAllEffects();
}
