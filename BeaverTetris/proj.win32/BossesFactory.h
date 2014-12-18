#pragma once

#include <vector>
#include <map>
#include "AIStrategyInterface.h"
#include "Tetramino.h"
#include "GameBoard.h"

class BossesFactory
{
public:
	BossesFactory(void);
	~BossesFactory(void);

	std::vector<AIStrategyInterface*> getBossAIstrategiesForBossType(Tetramino *aTetramino);

private:

	typedef std::vector<AIStrategyInterface*> (BossesFactory::*bossFactoryMethod) (void);

	GameBoard *_gameBoard;
	Tetramino *_tetramino;
	std::map<TetraminoType, bossFactoryMethod> _availableAIStrategiesPrototypes;

	std::map< TetraminoType, bossFactoryMethod> makeAIStrategiesHandlers();
	std::vector<AIStrategyInterface*> makePrincessBoss();
	std::vector<AIStrategyInterface*> makeKingBoss();

};

