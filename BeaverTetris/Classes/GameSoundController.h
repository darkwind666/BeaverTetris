#pragma once

#include "ServiceInterface.h"
#include <string>

class GameSoundController : public ServiceInterface
{
public:
	GameSoundController(void);
	~GameSoundController(void);

	void playSoundEffectForKey(std::string aKey);
	void playBackgroundSoundForKey(std::string aKey);
	void stopAllSounds();

	float getCurrentSoundEffectsVolume();
	float getCurrentBackgroundSoundVolume();
	
	void setCurrentSoundEffectsVolume(float aVolume);
	void setCurrentBackgroundSoundVolume(float aVolume);

private:

	int _currentBackgroundSoundID;
	float _currentSoundEffectsVolume;
	float _currentBackgroundSoundVolume;

};

