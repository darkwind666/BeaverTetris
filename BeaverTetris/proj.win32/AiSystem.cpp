#include "AiSystem.h"
#include <vector>

using namespace std;

AiSystem::AiSystem(CurrentBossDataSource *aCurrentBossDataSource)
{
	_currentBossDataSource = aCurrentBossDataSource;
}


AiSystem::~AiSystem(void)
{
}

void AiSystem::updateSystem(float deltaTime)
{

	vector<AIStrategyInterface*> aiStrategies = _currentBossDataSource->getCurrentBossesAIStrategies;

	vector<AIStrategyInterface*>::iterator aiStrategiesIterator;

	for (aiStrategiesIterator = aiStrategies.begin; aiStrategiesIterator != aiStrategies.end; aiStrategiesIterator++)
	{
		AIStrategyInterface *aiStrategy = *aiStrategiesIterator;
		aiStrategy->updateAI;
	}

}