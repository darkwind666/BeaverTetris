#include "AIMovementStrategy.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

AIMovementStrategy::AIMovementStrategy(GameBoard *aGameBoard, Tetramino *aTetramino)
{
	_gameBoard = aGameBoard;
	_bossTetramino = aTetramino;
	_currentUpdateState = 0;
	_lastTetraminoInBossPlace = new Tetramino();
}


AIMovementStrategy::~AIMovementStrategy(void)
{
}

void AIMovementStrategy::updateAI()
{

	/*_currentUpdateState++;

	if (_currentUpdateState >= tetraminoBossTimeIntervalConstant)
	{
		_currentUpdateState = 0;

		GamePositionOnBoard newBossPosition = getNewBossPosition();
		placeBossOnNewPosition(newBossPosition);

	}*/

}


GamePositionOnBoard AIMovementStrategy::getNewBossPosition()
{
	GamePositionOnBoard newBossPosition;
	
	while (1)
	{
		BossMovementType newMovementDirection = (BossMovementType)GameHelper::getRandomNumberFromUpInterval(kTurnDownMovement);
		newBossPosition = getNewBossPositionForDirectionType(newMovementDirection);
		if (checkPossitionPossibility(newBossPosition))
		{
			break;
		}
	}

	return newBossPosition;
}


GamePositionOnBoard AIMovementStrategy::getNewBossPositionForDirectionType(BossMovementType aMovementType)
{

	GamePositionOnBoard currentBossPosition = _gameBoard->getTetraminoPosition(_bossTetramino);
	GamePositionOnBoard newBossPosition = currentBossPosition;

	switch (aMovementType)
	{
	case kIdleMovement:
		break;
	case kTurnLeftMovement:
		newBossPosition.xPosition = newBossPosition.xPosition - 1;
		break;
	case kTurnRightMovement:
		newBossPosition.xPosition = newBossPosition.xPosition + 1;
		break;
	case kTurnUpMovement:
		newBossPosition.yPosition = newBossPosition.yPosition + 1;
		break;
	case kTurnDownMovement:
		newBossPosition.yPosition = newBossPosition.yPosition - 1;
		break;
	default:
		break;
	}

	return newBossPosition;

}

bool AIMovementStrategy::checkPossitionPossibility(GamePositionOnBoard aPossiblePosition)
{
	bool possitionPossibility = true;
	bool boardWidthPossibility = aPossiblePosition.xPosition > _gameBoard->getGameBoardWidth() ||aPossiblePosition.xPosition < 0;
	bool boardHeightPossibility = aPossiblePosition.yPosition > _gameBoard->getGameBoardWidth() ||aPossiblePosition.xPosition < 0;
	
	if (!boardWidthPossibility && !boardHeightPossibility)
	{
		
		if (aPossiblePosition.yPosition < _gameBoard->getGameBoardHeight() && aPossiblePosition.yPosition > 0)
		{
			Tetramino *tetraminoOnNewPosition = _gameBoard->getTetraminoForXYposition(aPossiblePosition.xPosition, aPossiblePosition.yPosition);
			Tetramino *tetraminoOnUpNewPosition = _gameBoard->getTetraminoForXYposition(aPossiblePosition.xPosition, aPossiblePosition.yPosition + 1);
			Tetramino *tetraminoOnDownNewPosition = _gameBoard->getTetraminoForXYposition(aPossiblePosition.xPosition, aPossiblePosition.yPosition - 1);

			if (tetraminoOnNewPosition->getTetraminoType() == kTetraminoEmpty && tetraminoOnDownNewPosition == _bossTetramino)
			{
				possitionPossibility = false;
			}

			if (tetraminoOnNewPosition->getTetraminoType() == kTetraminoEmpty && tetraminoOnDownNewPosition->getTetraminoType() == kTetraminoEmpty)
			{
				possitionPossibility = false;
			}

		}

	}
	else
	{
		possitionPossibility = false;
	}
	return possitionPossibility;
}

void AIMovementStrategy::placeBossOnNewPosition(GamePositionOnBoard newBossPosition)
{

	Tetramino *tetraminoOnNewPosition = _gameBoard->getTetraminoForXYposition(newBossPosition.xPosition, newBossPosition.yPosition);

	if (_bossTetramino != tetraminoOnNewPosition)
	{
		GamePositionOnBoard currentBossPosition = _gameBoard->getTetraminoPosition(_bossTetramino);
		_gameBoard->setTetraminoXYposition(_lastTetraminoInBossPlace, currentBossPosition.xPosition, currentBossPosition.yPosition);
		_gameBoard->setTetraminoXYposition(_bossTetramino, newBossPosition.xPosition, newBossPosition.yPosition);
		_lastTetraminoInBossPlace = tetraminoOnNewPosition;
	}
}