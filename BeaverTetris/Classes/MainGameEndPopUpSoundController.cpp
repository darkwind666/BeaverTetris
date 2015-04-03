#include "MainGameEndPopUpSoundController.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "GameFileExtensionMaker.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"

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
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
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
	string endGameSound = GameFileExtensionMaker::getSoundWithExtension(aKey);
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->playBackgroundSoundForKey(endGameSound);
}

void MainGameEndPopUpSoundController::stopPlayingSound()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	gameSoundController->stopAllSounds();
}
