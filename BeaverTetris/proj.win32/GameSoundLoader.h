#pragma once

#include "ResourcesLoader.h"

class GameSoundDataSource;

class SoundLoader
{
public:
	SoundLoader(void);
	~SoundLoader(void);

	virtual void loadResources();

private:

	GameSoundDataSource *_gameSoundDataSource;

};

