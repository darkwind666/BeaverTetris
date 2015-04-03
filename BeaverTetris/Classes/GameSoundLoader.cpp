#include "GameSoundLoader.h"
#include "GameSoundDataSource.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace std;
using namespace CocosDenshion;

GameSoundLoader::GameSoundLoader(void)
{
	_gameSoundDataSource = new GameSoundDataSource();
}

GameSoundLoader::~GameSoundLoader(void)
{
}

void GameSoundLoader::loadResources()
{
	loadEffects();
	loadBackgroundMusic();
}

void GameSoundLoader::loadEffects()
{
	int effectsCount = _gameSoundDataSource->getEffectsCount();
	for (int effectIndex = 0; effectIndex < effectsCount; effectIndex++)
	{
		loadEffectForIndex(effectIndex);
	}
}

void GameSoundLoader::loadEffectForIndex(int aSoundIndex)
{
	string effect = _gameSoundDataSource->getEffectForIndex(aSoundIndex);
	SimpleAudioEngine::sharedEngine()->preloadEffect(effect.c_str());
}

void GameSoundLoader::loadBackgroundMusic()
{
	int backgroundSoundsCount = _gameSoundDataSource->getBackgroundSoundsCount();
	for (int backgroundSoundIndex = 0; backgroundSoundIndex < backgroundSoundsCount; backgroundSoundIndex++)
	{
		loadBackgroundSoundIndexForIndex(backgroundSoundIndex);
	}
}

void GameSoundLoader::loadBackgroundSoundIndexForIndex(int aBackgroundSoundIndex)
{
	string backgroundSound = _gameSoundDataSource->getBackgroundSoundForIndex(aBackgroundSoundIndex);
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(backgroundSound.c_str());
}

