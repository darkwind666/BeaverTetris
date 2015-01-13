#pragma once

#include "ResourcesLoader.h"

class GameDataLoader : public ResourcesLoader
{
public:
	GameDataLoader(void);
	~GameDataLoader(void);

	virtual void loadResources();

};

