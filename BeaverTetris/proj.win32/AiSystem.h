#pragma once

#include "GameSystemInterface.h"
#include "CurrentBossDataSource.h"

class AiSystem
{
public:
	AiSystem(CurrentBossDataSource *aCurrentBossDataSource);
	~AiSystem(void);

	void updateSystem(float deltaTime);

private:

	CurrentBossDataSource *_currentBossDataSource;

};

