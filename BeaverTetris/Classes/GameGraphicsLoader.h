#pragma once

#include "ServiceInterface.h"

class GameGraphicsDataSource;

class GameGraphicsLoader : public ServiceInterface
{
public:
	GameGraphicsLoader(GameGraphicsDataSource *aGameGraphicsDataSource);
	~GameGraphicsLoader(void);

	void setInitialGraphic();

};

