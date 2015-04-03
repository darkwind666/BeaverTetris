#include "MainGameEndPopUpSoundController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "AudioEngine.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
using namespace experimental;

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
	AudioEngine::stopAll();
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
	string soundEffect = GameFileExtensionMaker::getSoundWithExtension(aKey);
	AudioEngine::play2d(soundEffect, true);
}

void MainGameEndPopUpSoundController::stopPlayingSound()
{
	AudioEngine::stopAll();
}
