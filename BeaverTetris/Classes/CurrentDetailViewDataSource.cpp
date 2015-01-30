#include "CurrentDetailViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "KeysForEnumsDataSource.h"
#include "GameFileExtensionMaker.h"

#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

CurrentDetailViewDataSource::CurrentDetailViewDataSource(void)
{
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}

CurrentDetailViewDataSource::~CurrentDetailViewDataSource(void)
{
}

int CurrentDetailViewDataSource::getTetraminosCount()
{
	int detailHeight = getCurrentDetail()->getDetailHeight();
	int detailWidth = getCurrentDetail()->getDetailWidth();
	return (detailHeight * detailWidth);
}

string CurrentDetailViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	Tetramino *tetraminoInDetail = getTetraminoOnIndex(aIndex);
	TetraminoType tetraminoType = tetraminoInDetail->getTetraminoType();
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

Vec2 CurrentDetailViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	GamePositionOnBoard tetraminoPosition = getCurrentDetail()->getPositionForIndex(aIndex);
	float xPosition = tetraminoPosition.xPosition * tetraminoOffset.x;
	float yPosition = tetraminoPosition.yPosition * tetraminoOffset.y;
	return Vec2(xPosition, yPosition);
}

bool CurrentDetailViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	Tetramino *tetraminoInBoard = getTetraminoOnIndex(aIndex);
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		availableTetramino = false;
	}
	return availableTetramino;
}

Vec2 CurrentDetailViewDataSource::getTetraminosViewOffset()
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	return tetraminoOffset;
}

TetraminoType CurrentDetailViewDataSource::getTetraminoTypeOnPositionInCurrentDetail(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard tetraminoPositionInDetail = getCurrentDetail()->convertAbsolutePositionToPositionInDetail(aPosition);
	Tetramino *tetraminoInDetail = getCurrentDetail()->getTetraminoForXY(tetraminoPositionInDetail.xPosition, tetraminoPositionInDetail.yPosition);
	return tetraminoInDetail->getTetraminoType();
}

Tetramino* CurrentDetailViewDataSource::getTetraminoOnIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = getCurrentDetail()->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = getCurrentDetail()->getTetraminoForXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	return tetraminoInBoard;
}

TetraminoDetail* CurrentDetailViewDataSource::getCurrentDetail()
{
	return _currentDetailDataSource->getCurrentDetail();
}
