#pragma once

#include "ServiceInterface.h"
#include <string>
#include "GameStructures.h"
#include <vector>

class GameLevelsDataSource : public ServiceInterface
{
public:
	GameLevelsDataSource(void);
	~GameLevelsDataSource(void);

	int getLevelsCount();
	std::string getLevelNameForIndex(int aIndex);
	GameLevelInformation getLevelDataForIndex(int aIndex);

private:

	std::vector<GameLevelInformation> _levelsInformation;

};

