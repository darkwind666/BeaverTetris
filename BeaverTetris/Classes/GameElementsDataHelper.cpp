#include "GameElementsDataHelper.h"

#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"

using namespace std;
using namespace cocos2d;

GameElementsDataHelper::GameElementsDataHelper(void)
{
}


GameElementsDataHelper::~GameElementsDataHelper(void)
{
}

Vec2 GameElementsDataHelper::getElementOffsetForKey(string aKey)
{
	GameViewElementsDataSource *viewElementsData = (GameViewElementsDataSource*) ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 offset = viewElementsData->getElementOffsetForKey(aKey);
	return offset;
}

Vec2 GameElementsDataHelper::getElementFinalActionPositionForKey(string aKey)
{
	GameViewElementsDataSource *viewElementsData = (GameViewElementsDataSource*) ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 finalPosition = viewElementsData->getElementFinalActionPositionForKey(aKey);
	return finalPosition;
}