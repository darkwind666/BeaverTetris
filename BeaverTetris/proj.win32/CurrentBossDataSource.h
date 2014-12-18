#pragma once

#include "AIStrategyInterface.h"
#include "CurrentLevelDataSource.h"
#include "GameBoard.h"
#include "BossesFactory.h"
#include <vector>
#include "GameEnums.h"

class CurrentBossDataSource
{
public:
	CurrentBossDataSource(CurrentLevelDataSource *aCurrentLevelDataSource, GameBoard *aGameBoard);
	~CurrentBossDataSource(void);

	std::vector<AIStrategyInterface*> getCurrentBossesAIStrategies();
	void refreshDataSource();

private:

	std::vector<AIStrategyInterface*> _currentBossesAIStrategies;
	CurrentLevelDataSource *_currentLevelDataSource;
	GameBoard *_gameBoard;
	BossesFactory *_bossesFactory;

	std::vector<AIStrategyInterface*> makeCurrentBossAIStrategies();
	void addBossStratagiesToAllStrategies(std::vector<AIStrategyInterface*> *bossStratagies, std::vector<AIStrategyInterface*> *allStrategies);

};

