#pragma once

#include "GameStructures.h"

class CurrentLevelDataSource
{
public:
	CurrentLevelDataSource(void);
	~CurrentLevelDataSource(void);

	GameLevelInformation getCurrentLevelData();

};

