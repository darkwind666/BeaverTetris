#pragma once

#include <string>
#include "GameStructures.h"

class GameLevelsDataSource
{
public:
	GameLevelsDataSource(void);
	~GameLevelsDataSource(void);

	int getLevelsCount;
	std::string getLevelNameForIndex(int aIndex);
	LevelInformation getLevelDataForIndex(int aIndex);

};

