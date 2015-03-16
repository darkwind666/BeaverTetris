#include "CurrentLevelDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"

using namespace std;

CurrentLevelDataSource::CurrentLevelDataSource(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_gameLevelsDataSource = (GameLevelsDataSource*)ServiceLocator::getServiceForKey(gameLevelsDataSourceKey);
}

CurrentLevelDataSource::~CurrentLevelDataSource(void)
{
}

GameLevelInformation CurrentLevelDataSource::getCurrentLevelData()
{
	int selectedLevelIndex = _currentPlayerDataSource->getSelectedGameLevelIndex();
	GameLevelInformation gameLevelInformation = _gameLevelsDataSource->getLevelDataForIndex(selectedLevelIndex);
	return gameLevelInformation;
}

bool CurrentLevelDataSource::finalLevel()
{
	bool finalLevel = false;
	int currentLevelIndex = _currentPlayerDataSource->getSelectedGameLevelIndex();
	int allLevelsCount = _gameLevelsDataSource->getLevelsCount() - 1;
	if (currentLevelIndex >= allLevelsCount)
	{
		finalLevel = true;
	}
	return finalLevel;
}
