#pragma once

#include "ResourcesLoader.h"

class GameSoundDataSource;

class GameSoundLoader : public ResourcesLoader
{
public:
	GameSoundLoader(void);
	~GameSoundLoader(void);

	virtual void loadResources();

private:

	GameSoundDataSource *_gameSoundDataSource;

	void loadEffects();
	void loadEffectForIndex(int aSoundIndex);
	void loadBackgroundMusic();
	void loadBackgroundSoundIndexForIndex(int aBackgroundSoundIndex);

};

