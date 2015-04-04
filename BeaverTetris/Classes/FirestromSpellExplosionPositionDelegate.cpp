#include "FirestromSpellExplosionPositionDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"
#include "GameDesignConstants.h"

using namespace std;

FirestromSpellExplosionPositionDelegate::FirestromSpellExplosionPositionDelegate(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
}


FirestromSpellExplosionPositionDelegate::~FirestromSpellExplosionPositionDelegate(void)
{
}

GamePositionOnBoard FirestromSpellExplosionPositionDelegate::getExplosionPositionFromMeteorX(int xPosition)
{
	int explosionHeight = getExplosionHeightFromExplosionX(xPosition);
	GamePositionOnBoard explosionPosition;
	explosionPosition.xPosition = xPosition;
	explosionPosition.yPosition = explosionHeight;
	return explosionPosition;
}

int FirestromSpellExplosionPositionDelegate::getExplosionHeightFromExplosionX(int xPosition)
{
	int explosionHeight = 0;
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	for (int heightIndex = (gameBoardHeight - 1); heightIndex > 0; heightIndex--)
	{
		if (checkExplosionInCurrentDetailWithXYPosition(xPosition, heightIndex))
		{
			explosionHeight = heightIndex + 1;
			break;
		}
		else
		{
			if (checkExplosionInBoardWithXYPosition(xPosition, heightIndex))
			{
				explosionHeight = heightIndex + 1;
				break;
			}
		}

	}
	return explosionHeight;
}

bool FirestromSpellExplosionPositionDelegate::checkExplosionInCurrentDetailWithXYPosition(int xPosition, int yPosition)
{
	bool inCurrentDetail = false;
	if (_currentDetailDataSource->currentDetailAvailable())
	{
		GamePositionOnBoard absolutePosition;
		absolutePosition.xPosition = xPosition;
		absolutePosition.yPosition = yPosition;
		inCurrentDetail = checkExplosionInCurrentDetailWithAbsolutePosition(absolutePosition);
	}
	return inCurrentDetail;
}

bool FirestromSpellExplosionPositionDelegate::checkExplosionInCurrentDetailWithAbsolutePosition(GamePositionOnBoard aPosition)
{
	bool inCurrentDetail = false;
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	if (currentDetail->absolutePositionInDetail(aPosition))
	{
		GamePositionOnBoard positionInDetail = currentDetail->convertAbsolutePositionToPositionInDetail(aPosition);
		Tetramino *tetraminoInCurrentDetail = currentDetail->getTetraminoForXY(positionInDetail.xPosition, positionInDetail.yPosition);
		if (tetraminoInCurrentDetail->getTetraminoType() > kTetraminoEmpty)
		{
			inCurrentDetail = true;
		}
	}
	return inCurrentDetail;
}

bool FirestromSpellExplosionPositionDelegate::checkExplosionInBoardWithXYPosition(int xPosition, int yPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, yPosition);
	bool inBoard = (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty);
	return inBoard;
}

bool FirestromSpellExplosionPositionDelegate::explosionInCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition)
{
	GamePositionOnBoard realExplosionPosition = aExplosionPosition;
	realExplosionPosition.yPosition = realExplosionPosition.yPosition - 1;
	bool inCurrentDetail = checkExplosionInCurrentDetailWithXYPosition(realExplosionPosition.xPosition, realExplosionPosition.yPosition);
	return inCurrentDetail;
}

vector<GamePositionOnBoard> FirestromSpellExplosionPositionDelegate::getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition)
{
	vector<GamePositionOnBoard> explosionZone;
	int upHeight = aExplosionPosition.yPosition + meteorAreaExplosionLength;
	int downHeight = aExplosionPosition.yPosition - meteorAreaExplosionLength;
	for (int heightIndex = downHeight; heightIndex <= upHeight; heightIndex++)
	{
		fillExplosionZoneRowWithPosition(explosionZone, heightIndex, aExplosionPosition);
	}
	return explosionZone;
}

void FirestromSpellExplosionPositionDelegate::fillExplosionZoneRowWithPosition(vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition)
{
	int upWidth = aExplosionPosition.xPosition + meteorAreaExplosionLength;
	int downWidth = aExplosionPosition.xPosition - meteorAreaExplosionLength;
	for (int widthIndex = downWidth; widthIndex <= upWidth; widthIndex++)
	{
		GamePositionOnBoard explosionPosition;
		explosionPosition.xPosition = widthIndex;
		explosionPosition.yPosition = row;
		if (_gameBoard->positionInBoard(explosionPosition))
		{
			explosionZone.push_back(explosionPosition);
		}
	}
}