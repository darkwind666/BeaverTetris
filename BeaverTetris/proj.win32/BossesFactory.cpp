#include "BossesFactory.h"
#include "AIMovementStrategy.h"
#include "AISpellCastsStrategy.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;

BossesFactory::BossesFactory(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_availableAIStrategiesPrototypes = map<TetraminoType, bossFactoryMethod>();
	_availableAIStrategiesPrototypes[kTetraminoBossPrincess] = &BossesFactory::makePrincessBoss;
	_availableAIStrategiesPrototypes[kTetraminoBossKing] = &BossesFactory::makeKingBoss;
}


BossesFactory::~BossesFactory(void)
{
}

vector<AIStrategyInterface*> BossesFactory::getBossAIstrategiesForBossType(Tetramino *aTetramino)
{
	_tetramino = aTetramino;
	TetraminoType tetraminoType = aTetramino->getTetraminoType();
	bossFactoryMethod factoryMethod = _availableAIStrategiesPrototypes[tetraminoType];
	return (this->*factoryMethod)();
}


vector<AIStrategyInterface*> BossesFactory::makePrincessBoss()
{
	vector<AIStrategyInterface*> princessStrategies;
	princessStrategies.push_back(new AIMovementStrategy(_gameBoard, _tetramino));
	return princessStrategies;
}

vector<AIStrategyInterface*> BossesFactory::makeKingBoss()
{
	vector<AIStrategyInterface*> kingStrategies;
	kingStrategies.push_back(new AIMovementStrategy(_gameBoard, _tetramino));
	kingStrategies.push_back(new AISpellCastsStrategy());
	return kingStrategies;
}

