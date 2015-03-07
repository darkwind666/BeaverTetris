#include "AIMovementStrategy.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "BossMovementObserver.h"
#include "TetraminosFactory.h"

AIMovementStrategy::AIMovementStrategy(GameBoard *aGameBoard, Tetramino *aTetramino)
{
	_gameBoard = aGameBoard;
	_bossTetramino = aTetramino; 
	_currentUpdateState = 0;
	TetraminosFactory *tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
	_lastTetraminoInBossPlace = tetraminosFactory->getNewTetraminoWithType(kTetraminoEmpty);
	_bossDirections = getBossDirections();
	_observer = NULL;
}

AIMovementStrategy::~AIMovementStrategy(void)
{
	delete _lastTetraminoInBossPlace;
}

map<BossMovementType, function<void(GamePositionOnBoard&)> > AIMovementStrategy::getBossDirections()
{
	map<BossMovementType, function<void(GamePositionOnBoard&)> > bossDirections;
	bossDirections[kTurnLeftMovement] = [](GamePositionOnBoard &position){
		position.xPosition = position.xPosition - 1;
	};
	bossDirections[kTurnRightMovement] = [](GamePositionOnBoard &position){
		position.xPosition = position.xPosition + 1;
	};
	bossDirections[kTurnUpMovement] = [](GamePositionOnBoard &position){
		position.yPosition = position.yPosition + 1;
	};
	bossDirections[kTurnDownMovement] = [](GamePositionOnBoard &position){
		position.yPosition = position.yPosition - 1;
	};
	return bossDirections;
}

void AIMovementStrategy::updateAI()
{
	_currentUpdateState++;
	if (_currentUpdateState >= tetraminoBossMoveTimeIntervalConstant)
	{
		_currentUpdateState = 0;
		GamePositionOnBoard newBossPosition = getNewBossPosition();
		sendObserverMessageWithNewBossPosition(newBossPosition);
		placeBossOnNewPosition(newBossPosition);
	}
}

GamePositionOnBoard AIMovementStrategy::getNewBossPosition()
{
	BossMovementType newMovementDirection = (BossMovementType)GameHelper::getRandomNumberFromUpInterval(kTurnDownMovement);
	GamePositionOnBoard newBossPosition = getNewBossPositionForDirectionType(newMovementDirection);
	while (checkPossitionPossibility(newBossPosition) == false)
	{
		newMovementDirection = (BossMovementType)GameHelper::getRandomNumberFromUpInterval(kIdleMovement);
		newBossPosition = getNewBossPositionForDirectionType(newMovementDirection);
	}
	return newBossPosition;
}


GamePositionOnBoard AIMovementStrategy::getNewBossPositionForDirectionType(BossMovementType aMovementType)
{
	GamePositionOnBoard newBossPosition = _gameBoard->getTetraminoPosition(_bossTetramino);
	function<void(GamePositionOnBoard&)> directionFactory = _bossDirections[aMovementType];
	directionFactory(newBossPosition);
	return newBossPosition;
}

bool AIMovementStrategy::checkPossitionPossibility(GamePositionOnBoard aPossiblePosition)
{
	bool possitionPossibility = false;
	if (_gameBoard->positionInBoard(aPossiblePosition))
	{
		Tetramino *tetraminoOnPosition  = _gameBoard->getTetraminoForXYposition(aPossiblePosition.xPosition, aPossiblePosition.yPosition);
		if (bossTypeEqualTetraminoType(tetraminoOnPosition) == false)
		{
			possitionPossibility = true;
		}
	}
	return possitionPossibility;
}

bool AIMovementStrategy::bossTypeEqualTetraminoType(Tetramino *aTetramino)
{
	TetraminoType bossType = _bossTetramino->getTetraminoType();
	TetraminoType tetraminoOnPositionType = aTetramino->getTetraminoType();
	return (bossType == tetraminoOnPositionType);
}

void AIMovementStrategy::placeBossOnNewPosition(GamePositionOnBoard newBossPosition)
{
	Tetramino *tetraminoOnNewPosition = _gameBoard->getTetraminoForXYposition(newBossPosition.xPosition, newBossPosition.yPosition);
	GamePositionOnBoard currentBossPosition = _gameBoard->getTetraminoPosition(_bossTetramino);
	_gameBoard->setTetraminoXYposition(_lastTetraminoInBossPlace, currentBossPosition.xPosition, currentBossPosition.yPosition);
	_gameBoard->setTetraminoXYposition(_bossTetramino, newBossPosition.xPosition, newBossPosition.yPosition);
	_lastTetraminoInBossPlace = tetraminoOnNewPosition;
}

void AIMovementStrategy::addObserver(BossMovementObserver *aObserver)
{
	_observer = aObserver;
}

void AIMovementStrategy::sendObserverMessageWithNewBossPosition(GamePositionOnBoard newBossPosition)
{
	if (_observer)
	{
		GamePositionOnBoard startBossPosition = _gameBoard->getTetraminoPosition(_bossTetramino);
		_observer->moveBossFromStartPositionToFinal(startBossPosition, newBossPosition);
	}
}