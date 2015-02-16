#include "TetraminosChainCleaner.h"
#include "ExplosionAnimationDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "AwardForTetraminoDataSource.h"
#include "GameDesignConstants.h"

using namespace std;

TetraminosChainCleaner::TetraminosChainCleaner(GameBoard *aGameBoard)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
	_gameBoard = aGameBoard;
	_delegate = NULL;
}


TetraminosChainCleaner::~TetraminosChainCleaner(void)
{
}

void TetraminosChainCleaner::setDelegate(ExplosionAnimationDelegate *aDelegate)
{
	_delegate = aDelegate;
}

void TetraminosChainCleaner::cleanChain(vector<GamePositionOnBoard> aPositions)
{
	sendMassageToDelegateWithTetraminos(aPositions);
	setAwardToPlayerFromTetraminos(aPositions);
	removeTetraminosWithPositions(aPositions);
}


void TetraminosChainCleaner::setAwardToPlayerFromTetraminos(vector<GamePositionOnBoard> aTetraminos)
{
	if (_delegate == NULL)
	{
		setTetraminosAward(aTetraminos);
	}
}

void TetraminosChainCleaner::setTetraminosAward(std::vector<GamePositionOnBoard> aTetraminos)
{
	int awardForChain = getAwardForChainForTetraminos(aTetraminos);
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
	_currentPlayerDataSource->setPlayerScore(currentPlayerScore + awardForChain);
}

int TetraminosChainCleaner::getAwardForChainForTetraminos(vector<GamePositionOnBoard> aTetraminos)
{
	int award = 0;
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
		award += (_awardForTetraminoDataSource->getAwardForTetraminoType(tetraminoInBoard->getTetraminoType())) + prizeForChainConstant;
	}
	return award;
}

void TetraminosChainCleaner::removeTetraminosWithPositions(vector<GamePositionOnBoard> aTetraminos)
{
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
		_gameBoard->removeTetraminoForXYposition(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
		delete tetraminoInBoard;
	}
}

void TetraminosChainCleaner::sendMassageToDelegateWithTetraminos(vector<GamePositionOnBoard> aTetraminos)
{
	if (_delegate)
	{
		_delegate->blowUpTetraminosForPositions(aTetraminos);
		sendRemoveTetraminosMassagesToDelegate(aTetraminos);
		sendCallbackWithAwardForTetraminosToDelegate(aTetraminos);
	}
}

void TetraminosChainCleaner::sendRemoveTetraminosMassagesToDelegate(vector<GamePositionOnBoard> aTetraminos)
{
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		_delegate->removeTetraminoOnPositionXY(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
	}
}

void TetraminosChainCleaner::sendCallbackWithAwardForTetraminosToDelegate(vector<GamePositionOnBoard> aTetraminos)
{
	function<void()> callback = [this, aTetraminos](){
			setTetraminosAward(aTetraminos);
		};
	_delegate->setCallback(callback);
}