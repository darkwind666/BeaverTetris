#include "PlaceSomeDetailsCondition.h"
#include "NewTetraminoDetailDataSource.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;

PlaceSomeDetailsCondition::PlaceSomeDetailsCondition(GameLevelInformation aLevelInformation)
{
	_needToPlaceDetailsCount = aLevelInformation.needToPlaceDetailsCount;
	_newTetraminoDetailDataSource = (NewTetraminoDetailDataSource*)ServiceLocator::getServiceForKey(newTetraminoDetailDataSourceKey);
}


PlaceSomeDetailsCondition::~PlaceSomeDetailsCondition(void)
{
}

int PlaceSomeDetailsCondition::getVictoryStateInformationCount(void)
{
	return 1;
}

int PlaceSomeDetailsCondition::getVictoryStateInformationForIndex(int aIndex)
{
	int placedDetailsCount = _newTetraminoDetailDataSource->getCreatedDetailsCount();
	int remainDetailsCount = _needToPlaceDetailsCount - placedDetailsCount;
	return remainDetailsCount;
}

string PlaceSomeDetailsCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	return placeDetailsIconKey;
}

bool PlaceSomeDetailsCondition::playerWin(void)
{
	bool playerWin = false;
	int placedDetailsCount = _newTetraminoDetailDataSource->getCreatedDetailsCount();
	if (placedDetailsCount >= _needToPlaceDetailsCount)
	{
		playerWin = true;
	}
	return playerWin;
}

void PlaceSomeDetailsCondition::update(void)
{
	
}