#include "PlaceSomeDetailsCondition.h"
#include "GameViewElementsKeys.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;

PlaceSomeDetailsCondition::PlaceSomeDetailsCondition(GameLevelInformation aLevelInformation)
{
	_needToPlaceDetailsCount = aLevelInformation.needToPlaceDetailsCount;
	_tetraminisDetailsFactory = (TetraminisDetailsFactory*)ServiceLocator::getServiceForKey(tetraminisDetailsFactoryKey);
	update();
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
	 return _placedDetailsCount;
}

string PlaceSomeDetailsCondition::getVictoryStateIconImageForIndex(int aIndex)
{
	return placeDetailsIconKey;
}

bool PlaceSomeDetailsCondition::playerWin(void)
{
	bool playerWin = false;

	if (_placedDetailsCount >= _needToPlaceDetailsCount)
	{
		playerWin = true;
	}
	return playerWin;
}

void PlaceSomeDetailsCondition::update(void)
{
	_placedDetailsCount = _tetraminisDetailsFactory->getCreatedDetailsCount();
}