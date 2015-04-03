#include "GameSoundDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameSoundsKeys.h"

using namespace std;

GameSoundDataSource::GameSoundDataSource(void)
{
	_effects = getEffects();
	_backgroundSounds = getBackgroundSounds();
}


GameSoundDataSource::~GameSoundDataSource(void)
{
}

vector<string> GameSoundDataSource::getEffects()
{
	vector<string> effects;

	effects.push_back(buttonPressedSoundKey);
	effects.push_back(detailFallingSoundKey);
	effects.push_back(explosionSoundKey);
	effects.push_back(tetraminoAppearSoundKey);
	effects.push_back(rocketLaunchSoundKey);
	effects.push_back(winLevelSoundKey);
	effects.push_back(loseLevelSoundKey);
	effects.push_back(winAllGameSoundKey);

	return effects;
}

vector<string> GameSoundDataSource::getBackgroundSounds()
{
	vector<string> backgroundSounds;

	backgroundSounds.push_back(waterSoundKey);
	backgroundSounds.push_back(birdInForestSoundKey);
	backgroundSounds.push_back(backgroundSound1Key);
	backgroundSounds.push_back(backgroundSound2Key);

	return backgroundSounds;
}

int GameSoundDataSource::getEffectsCount()
{
	return _effects.size();
}

string  GameSoundDataSource::getEffectForIndex(int aIndex)
{
	string effect = _effects[aIndex];
	string effectWithFileExtension = GameFileExtensionMaker::getSoundWithExtension(effect);
	return effectWithFileExtension;
}

int GameSoundDataSource::getBackgroundSoundsCount()
{
	return _backgroundSounds.size();
}

string  GameSoundDataSource::getBackgroundSoundForIndex(int aIndex)
{
	string backgroundSound = _backgroundSounds[aIndex];
	string backgroundSoundWithFileExtension = GameFileExtensionMaker::getSoundWithExtension(backgroundSound);
	return backgroundSoundWithFileExtension;
}
