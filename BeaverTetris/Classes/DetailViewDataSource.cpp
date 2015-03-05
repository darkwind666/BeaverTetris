#include "DetailViewDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"
#include "KeysForEnumsDataSource.h"
#include "GameFileExtensionMaker.h"

#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

DetailViewDataSource::DetailViewDataSource(function<TetraminoDetail*()> aDetailDataSource)
{
	_detailDataSource = aDetailDataSource;
	_keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
}

DetailViewDataSource::~DetailViewDataSource(void)
{
}

int DetailViewDataSource::getTetraminosCount()
{
	int detailHeight = getCurrentDetail()->getDetailHeight();
	int detailWidth = getCurrentDetail()->getDetailWidth();
	return (detailHeight * detailWidth);
}

string DetailViewDataSource::getTetraminoImageForIndex(int aIndex)
{
	Tetramino *tetraminoInDetail = getTetraminoOnIndex(aIndex);
	TetraminoType tetraminoType = tetraminoInDetail->getTetraminoType();
	string tetraminoKey = _keysForEnumsDataSource->getKeyForTetraminoType(tetraminoType);
	return GameFileExtensionMaker::getGraphicWithExtension(tetraminoKey);
}

Vec2 DetailViewDataSource::getTetraminoPositionForIndex(int aIndex)
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	GamePositionOnBoard tetraminoPosition = getCurrentDetail()->getPositionForIndex(aIndex);
	float xPosition = tetraminoPosition.xPosition * tetraminoOffset.x;
	float yPosition = tetraminoPosition.yPosition * tetraminoOffset.y;
	return Vec2(xPosition, yPosition);
}

bool DetailViewDataSource::availableTetraminoOnIndex(int aIndex)
{
	bool availableTetramino = true;
	Tetramino *tetraminoInBoard = getTetraminoOnIndex(aIndex);
	if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
	{
		availableTetramino = false;
	}
	return availableTetramino;
}

Vec2 DetailViewDataSource::getTetraminosViewOffset()
{
	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	return tetraminoOffset;
}

Vec2 DetailViewDataSource::getDetailPositionOnView()
{
	GamePositionOnBoard currentDetailPosition = getCurrentDetail()->getDetailPosition();
	Vec2 detailPositionOnView = getPositionOnView(currentDetailPosition);
	return detailPositionOnView;
}

Vec2 DetailViewDataSource::getPositionOnView(GamePositionOnBoard aPosition)
{
	Vec2 offset = getTetraminosViewOffset();
	Vec2 detailPositionOnView(aPosition.xPosition * offset.x, aPosition.yPosition * offset.y);
	return detailPositionOnView;
}

GamePositionOnBoard DetailViewDataSource::getTetraminoPositionInBoardForIndex(int aIndex)
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	GamePositionOnBoard positionInDetail = currentDetail->getPositionForIndex(aIndex);
	GamePositionOnBoard positionInBoard = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
	return positionInBoard;
}

GamePositionOnBoard DetailViewDataSource::getDetailPositionOnBoard()
{
	TetraminoDetail *currentDetail = getCurrentDetail();
	return currentDetail->getDetailPosition();
}

string DetailViewDataSource::getTetraminoImageForAbsolutePosition(GamePositionOnBoard aPosition)
{
	GamePositionOnBoard tetraminoPositionInDetail = getCurrentDetail()->convertAbsolutePositionToPositionInDetail(aPosition);
	int tetraminoIndex = getCurrentDetail()->getIndexForPosition(tetraminoPositionInDetail);
	string tetraminoImage = getTetraminoImageForIndex(tetraminoIndex);
	return tetraminoImage;
}

Tetramino* DetailViewDataSource::getTetraminoOnIndex(int aIndex)
{
	GamePositionOnBoard tetraminoPosition = getCurrentDetail()->getPositionForIndex(aIndex);
	Tetramino *tetraminoInBoard = getCurrentDetail()->getTetraminoForXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	return tetraminoInBoard;
}

void DetailViewDataSource::cleanDetailWithCleanerCallback(DetailCleaner aCleanerCallback)
{
	TetraminoDetail *currentDetail =  getCurrentDetail();
	int detailWidth = currentDetail->getDetailWidth();
	int detailHeight = currentDetail->getDetailHeight();
	
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
		{
			cleanTetraminoWithCleanerForXY(aCleanerCallback, widthIndex, heightIndex);
		}
	}
}

void DetailViewDataSource::cleanTetraminoWithCleanerForXY(DetailCleaner aCleanerCallback, int xPosition, int yPosition)
{
	TetraminoDetail *currentDetail =  getCurrentDetail();
	GamePositionOnBoard positionInDetail;
	positionInDetail.xPosition = xPosition;
	positionInDetail.yPosition = yPosition;

	Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(xPosition, yPosition);

	if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
	{
		GamePositionOnBoard absolutePosition = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
		aCleanerCallback(absolutePosition);
	}
}

TetraminoDetail* DetailViewDataSource::getCurrentDetail()
{
	return _detailDataSource();
}
