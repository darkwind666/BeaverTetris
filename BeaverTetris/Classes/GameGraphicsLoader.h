#pragma once

#include "proj.win32\ServiceInterface.h"

class GameGraphicsDataSource;

class GameGraphicsLoader : public ServiceInterface
{
public:
	GameGraphicsLoader(GameGraphicsDataSource *aGameGraphicsDataSource);
	~GameGraphicsLoader(void);

	void setInitialGraphic();

};

