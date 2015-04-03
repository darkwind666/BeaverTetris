#include "GameSoundController.h"
#include "AudioEngine.h"
#include "cocos2d.h"
#include "GameDesignConstants.h"

using namespace std;
using namespace cocos2d::experimental;

GameSoundController::GameSoundController(void)
{
	_currentSoundEffectsVolume = startSoundEffectsVolume;
	_currentBackgroundSoundVolume = startBackgroundSoundVolume;
	_currentBackgroundSoundID = 0;
}


GameSoundController::~GameSoundController(void)
{
}

void GameSoundController::playSoundEffectForKey(string aKey)
{
	AudioEngine::play2d(aKey, false, _currentSoundEffectsVolume);
}

void GameSoundController::playBackgroundSoundForKey(string aKey)
{
	_currentBackgroundSoundID = AudioEngine::play2d(aKey, true, _currentBackgroundSoundVolume);
}

void GameSoundController::stopAllSounds()
{
	AudioEngine::stopAll();
}

float GameSoundController::getCurrentSoundEffectsVolume()
{
	return _currentSoundEffectsVolume;
}

float GameSoundController::getCurrentBackgroundSoundVolume()
{
	return _currentBackgroundSoundVolume;
}

void GameSoundController::setCurrentSoundEffectsVolume(float aVolume)
{
	_currentSoundEffectsVolume = aVolume;
}

void GameSoundController::setCurrentBackgroundSoundVolume(float aVolume)
{
	_currentBackgroundSoundVolume = aVolume;
	AudioEngine::setVolume(_currentBackgroundSoundID, aVolume);
}

