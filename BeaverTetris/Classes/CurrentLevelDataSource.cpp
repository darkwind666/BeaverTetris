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
	GameLevelInformation gameLevelInformation;

	vector<TetraminoType> availableTetraminos;

	availableTetraminos.push_back(kTetraminoRed);
	availableTetraminos.push_back(kTetraminoGreen);
	availableTetraminos.push_back(kTetraminoBlue);
	availableTetraminos.push_back(kTetraminoGold);
	availableTetraminos.push_back(kTetraminoBlack);

	gameLevelInformation.availableTetraminos = availableTetraminos;

	vector<TetraminoDetailType> availableTetraminoDetails;

	availableTetraminoDetails.push_back(kTetraminoDetail1);
	availableTetraminoDetails.push_back(kTetraminoDetail2);
	availableTetraminoDetails.push_back(kTetraminoDetail3);
	availableTetraminoDetails.push_back(kTetraminoDetail4);
	availableTetraminoDetails.push_back(kTetraminoDetail5);
	availableTetraminoDetails.push_back(kTetraminoDetail6);
	availableTetraminoDetails.push_back(kTetraminoDetail7);
	availableTetraminoDetails.push_back(kTetraminoDetail8);

	gameLevelInformation.availableTetraminoDetails = availableTetraminoDetails;

	TetraminoBossesInformation availableBosses;
	availableBosses.aBossType = kTetraminoBossKing;
	availableBosses.bossesCount = 1;

	gameLevelInformation.availableBosses = availableBosses;
	gameLevelInformation.victoryConditionType = kWinBossCondition;

	gameLevelInformation.needToPlaceDetailsCount = 100;

	gameLevelInformation.remainTimes = 200;



	std::vector<TetraminosForWinInformation> tetraminosCollectionForWin;

	TetraminosForWinInformation tetraminoType1;
	tetraminoType1.tetraminoType = kTetraminoRed;
	tetraminoType1.tetraminosCount = 20;

	TetraminosForWinInformation tetraminoType2;
	tetraminoType2.tetraminoType = kTetraminoGreen;
	tetraminoType2.tetraminosCount = 10;


	tetraminosCollectionForWin.push_back(tetraminoType1);
	tetraminosCollectionForWin.push_back(tetraminoType2);

	gameLevelInformation.tetraminosCollectionForWin = tetraminosCollectionForWin;

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
