#include "VictoryConditionViewDataSource.h"
#include "CurrentVictoryConditionDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameViewConstants.h"
#include "GameElementsDataHelper.h"
#include "StringsSupporter.h"

using namespace std;
using namespace cocos2d;

VictoryConditionViewDataSource::VictoryConditionViewDataSource(CurrentVictoryConditionDataSource *currentVictoryConditionDataSource)
{
	_currentVictoryCondition = currentVictoryConditionDataSource->getCurrentVictoryCondition();
	_gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
}


VictoryConditionViewDataSource::~VictoryConditionViewDataSource(void)
{
}

int VictoryConditionViewDataSource::getVictoryConditionsCount(void)
{
	int victoryConditionsCount = _currentVictoryCondition->getVictoryStateInformationCount();
	return victoryConditionsCount;
}

string VictoryConditionViewDataSource::getVictoryConditionIconImageForIndex(int aIndex)
{
	string victoryConditionIconImage = _currentVictoryCondition->getVictoryStateIconImageForIndex(aIndex);
	return victoryConditionIconImage;
}

Vec2 VictoryConditionViewDataSource::getVictoryConditionIconImagePositionForIndex(int aIndex)
{
	Vec2 startImagePosition = _gameViewElementsDataSource->getElementPositionForKey(victoryConditionHudImageKey);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(victoryConditionHudImageKey);
	float lengthPart = offset.x / (getVictoryConditionsCount() + 1);
	Vec2 imagePosition = Vec2(startImagePosition.x + (lengthPart * aIndex),  startImagePosition.y);
	return imagePosition;
}

string VictoryConditionViewDataSource::getVictoryConditionInformationForIndex(int aIndex)
{
	int stateInformation = _currentVictoryCondition->getVictoryStateInformationForIndex(aIndex);
	string victoryConditionInformation = StringsSupporter::getStringFromNumber(stateInformation);
	return victoryConditionInformation;
}

Vec2 VictoryConditionViewDataSource::getVictoryConditionInformationPositionForIndex(int aIndex)
{
	Vec2 startPosition = _gameViewElementsDataSource->getElementPositionForKey(victoryConditionHudStateKey);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(victoryConditionHudStateKey);
	float lengthPart = offset.x / (getVictoryConditionsCount() + 1);
	Vec2 stateInformationPosition = Vec2(startPosition.x + (lengthPart * aIndex),  startPosition.y);
	return stateInformationPosition;
}
