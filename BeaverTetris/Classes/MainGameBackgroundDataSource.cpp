#include "MainGameBackgroundDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "CurrentPlayerDataSource.h"
#include "GameLevelsDataSource.h"
#include "GameFileExtensionMaker.h"

using namespace std;

MainGameBackgroundDataSource::MainGameBackgroundDataSource(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_gameLevelsDataSource = (GameLevelsDataSource*)ServiceLocator::getServiceForKey(gameLevelsDataSourceKey);
}


MainGameBackgroundDataSource::~MainGameBackgroundDataSource(void)
{
}

string MainGameBackgroundDataSource::getCurrentLevelBackground()
{
	int currentLevelIndex = _currentPlayerDataSource->getSelectedGameLevelIndex();
	string levelName = _gameLevelsDataSource->getLevelNameForIndex(currentLevelIndex);
	return GameFileExtensionMaker::getGraphicWithExtension(levelName);
}