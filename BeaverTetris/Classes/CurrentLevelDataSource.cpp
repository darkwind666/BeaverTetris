#include "CurrentLevelDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"

using namespace std;

CurrentLevelDataSource::CurrentLevelDataSource(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
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

	gameLevelInformation.availableTetraminoDetails = availableTetraminoDetails;

	TetraminoBossesInformation availableBosses;
	availableBosses.aBossType = kTetraminoBossKing;
	availableBosses.bossesCount = 1;

	gameLevelInformation.availableBosses = availableBosses;
	gameLevelInformation.victoryConditionType = kRemainSomeTimeCondition;

	gameLevelInformation.needToPlaceDetailsCount = 10;

	gameLevelInformation.remainTimes = 200;

	return gameLevelInformation;
}

