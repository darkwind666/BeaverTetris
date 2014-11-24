#pragma once

#include "ServiceInterface.h"
#include <string>
#include "GameStructures.h"

class GameLevelsDataSource : public ServiceInterface
{
public:
	GameLevelsDataSource(void);
	~GameLevelsDataSource(void);

	int getLevelsCount;
	std::string getLevelNameForIndex(int aIndex);
	LevelInformation getLevelDataForIndex(int aIndex);

};

