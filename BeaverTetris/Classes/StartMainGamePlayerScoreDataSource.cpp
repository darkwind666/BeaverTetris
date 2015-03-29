#include "StartMainGamePlayerScoreDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"

StartMainGamePlayerScoreDataSource::StartMainGamePlayerScoreDataSource(void)
{
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_currentPlayerDataSource = currentPlayerDataSource;
	_startGamePlayerScore = currentPlayerDataSource->getPlayerScore();
}


StartMainGamePlayerScoreDataSource::~StartMainGamePlayerScoreDataSource(void)
{
}

void StartMainGamePlayerScoreDataSource::restorePlayerScore()
{
	_currentPlayerDataSource->setPlayerScore(_startGamePlayerScore);
}
