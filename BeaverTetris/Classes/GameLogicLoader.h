#pragma once

#include "ResourcesLoader.h"

class GameLogicLoader : public ResourcesLoader
{
public:
	GameLogicLoader(void);
	~GameLogicLoader(void);

	virtual void loadResources();

private:

	void setUpMainGameLogic();

};

