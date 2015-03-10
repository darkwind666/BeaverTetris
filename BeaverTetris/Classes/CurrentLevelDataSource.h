#pragma once

#include "GameStructures.h"
#include "ServiceInterface.h"

class CurrentPlayerDataSource;
class GameLevelsDataSource;

class CurrentLevelDataSource : public ServiceInterface
{
public:
	CurrentLevelDataSource(void);
	~CurrentLevelDataSource(void);

	GameLevelInformation getCurrentLevelData();
	bool finalLevel();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameLevelsDataSource *_gameLevelsDataSource;

};

