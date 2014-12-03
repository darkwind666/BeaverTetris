#include "BossesFactory.h"
#include "AIMovementStrategy.h"
#include "AISpellCastsStrategy.h"

using namespace std;

BossesFactory::BossesFactory(void)
{
	_availableAIStrategiesPrototypes = map<TetraminoType, bossFactoryMethod>();
	_availableAIStrategiesPrototypes[kTetraminoBossPrincess] = &BossesFactory::makePrincessBoss;
	_availableAIStrategiesPrototypes[kTetraminoBossKing] = &BossesFactory::makeKingBoss;
}


BossesFactory::~BossesFactory(void)
{
}

vector<AIStrategyInterface*> BossesFactory::getBossAIstrategiesForBossType(Tetramino *aTetramino)
{

	bossFactoryMethod factoryMethod = _availableAIStrategiesPrototypes[aTetramino->getTetraminoType];
	return (this->*factoryMethod)();
}


vector<AIStrategyInterface*> BossesFactory::makePrincessBoss()
{
	vector<AIStrategyInterface*> princessStrategies;
	princessStrategies.push_back(new AIMovementStrategy());
	return princessStrategies;
}

vector<AIStrategyInterface*> BossesFactory::makeKingBoss()
{
	vector<AIStrategyInterface*> kingStrategies;
	kingStrategies.push_back(new AIMovementStrategy());
	kingStrategies.push_back(new AISpellCastsStrategy());
	return kingStrategies;
}

