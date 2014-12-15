#include "VictoryConditionViewDataSource.h"
#include "GameViewConstants.h"
#include "StringsSupporter.h"

using namespace std;
using namespace cocos2d;

VictoryConditionViewDataSource::VictoryConditionViewDataSource(VictoryConditionsFactory *aGameVictoryFactory, PlayerSelectionDataSource *aPlayerSelectionDataSource)
{
	_gameVictoryFactory = aGameVictoryFactory;
	_playerSelectionDataSource = aPlayerSelectionDataSource;
	refreshDataSource();
}


VictoryConditionViewDataSource::~VictoryConditionViewDataSource(void)
{
}

int VictoryConditionViewDataSource::getVictoryConditionsCount(void)
{
	int victoryConditionsCount = _currentVictoryCondition->getVictoryStateInformationCount;
	return victoryConditionsCount;
}

string VictoryConditionViewDataSource::getVictoryConditionIconImageForIndex(int aIndex)
{
	string victoryConditionIconImage = _currentVictoryCondition->getVictoryStateIconImageForIndex(aIndex);
	return victoryConditionIconImage;
}

Vec2 VictoryConditionViewDataSource::getVictoryConditionIconImagePositionForIndex(int aIndex)
{
	return Vec2(50,50);
}

string VictoryConditionViewDataSource::getVictoryConditionInformationForIndex(int aIndex)
{
	int stateInformation = _currentVictoryCondition->getVictoryStateInformationForIndex(aIndex);
	string victoryConditionInformation = StringsSupporter::getStringFromNumber(stateInformation);
	return victoryConditionInformation;
}

Vec2 VictoryConditionViewDataSource::getVictoryConditionInformationPositionForIndex(int aIndex)
{
	Vec2 iconPosition = getVictoryConditionIconImagePositionForIndex(aIndex);
	Vec2 informationPosition = iconPosition + Vec2(0,victoryConditionInformationYOffset);
	return informationPosition;
}

void VictoryConditionViewDataSource::refreshDataSource()
{
	int currentLevelIndex = _playerSelectionDataSource->getSelectedGameLevel;
	_currentVictoryCondition = _gameVictoryFactory->makeVictoryConditionForLevelIndex(currentLevelIndex);
}