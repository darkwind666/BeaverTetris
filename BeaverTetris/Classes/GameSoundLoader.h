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

};

