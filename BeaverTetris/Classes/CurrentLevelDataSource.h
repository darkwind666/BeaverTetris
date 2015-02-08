#pragma once

#include "GameStructures.h"
#include "ServiceInterface.h"

class CurrentPlayerDataSource;

class CurrentLevelDataSource : public ServiceInterface
{
public:
	CurrentLevelDataSource(void);
	~CurrentLevelDataSource(void);

	GameLevelInformation getCurrentLevelData();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;

};

