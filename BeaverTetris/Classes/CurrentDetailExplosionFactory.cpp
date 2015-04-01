#include "CurrentDetailExplosionFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoExplosionFactory.h"
#include "TetraminoDetail.h"
#include "Tetramino.h"

using namespace cocos2d;

CurrentDetailExplosionFactory::CurrentDetailExplosionFactory(GameBoardController *aGameBoardController)
{
	TetraminoExplosionFactory *tetraminoExplosionFactory = new TetraminoExplosionFactory(aGameBoardController);
	_tetraminoExplosionFactory = tetraminoExplosionFactory;
	this->addChild(tetraminoExplosionFactory);
	CurrentDetailDataSource *currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_currentDetailDataSource = currentDetailDataSource;
}


CurrentDetailExplosionFactory::~CurrentDetailExplosionFactory(void)
{
}

FiniteTimeAction* CurrentDetailExplosionFactory::getCurrentDetailExplosionAnimation()
{
	vector<GamePositionOnBoard> explosionsPositions = getExplosionsPositions();
	FiniteTimeAction *explosions = _tetraminoExplosionFactory->getTetraminosExplosionsAnimationWithPositions(explosionsPositions);
	return explosions;
}

vector<GamePositionOnBoard> CurrentDetailExplosionFactory::getExplosionsPositions()
{
	vector<GamePositionOnBoard> explosionsPositions;
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailHeight = currentDetail->getDetailHeight();
	for (int heightIndex = 0; heightIndex < detailHeight; heightIndex++)
	{
		fillExplosionsPositionsFromLine(explosionsPositions, heightIndex);
	}
	return explosionsPositions;
}

void CurrentDetailExplosionFactory::fillExplosionsPositionsFromLine(vector<GamePositionOnBoard> &explosionsPositions, int aLine)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	int detailWidth = currentDetail->getDetailWidth();
	for (int widthIndex = 0; widthIndex < detailWidth; widthIndex++)
	{
		Tetramino *tetraminoInDetail = currentDetail->getTetraminoForXY(widthIndex, aLine);
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			fillExplosionsPositionsFromXY(explosionsPositions, widthIndex, aLine);
		}
	}
}

void CurrentDetailExplosionFactory::fillExplosionsPositionsFromXY(vector<GamePositionOnBoard> &explosionsPositions, int xPosition, int yPosition)
{
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	GamePositionOnBoard positionInDetail;
	positionInDetail.xPosition = xPosition;
	positionInDetail.yPosition = yPosition;
	GamePositionOnBoard absolutePosition = currentDetail->convertPositionInDetailToAbsolutePosition(positionInDetail);
	explosionsPositions.push_back(absolutePosition);
}