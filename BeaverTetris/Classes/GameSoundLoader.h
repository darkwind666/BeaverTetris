#pragma once

#include "ResourcesLoader.h"

class GameSoundLoader : public ResourcesLoader
{
public:
	GameSoundLoader(void);
	~GameSoundLoader(void);

	virtual void loadResources();

private:

};

