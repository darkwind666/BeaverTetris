#include "TetraminosChainCleaner.h"
#include "ExplosionAnimationDelegate.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "TetraminosFactory.h"

using namespace std;

TetraminosChainCleaner::TetraminosChainCleaner(GameBoard *aGameBoard)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_gameBoard = aGameBoard;
	TetraminosFactory *tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
	_prizeForChainConstant = tetraminosFactory->getAwardForElementInTetraminosChain();
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
		int awardForChain = getAwardForChainForTetraminos(aTetraminos);
		addAwardToPlayer(awardForChain);
	}
}

void TetraminosChainCleaner::addAwardToPlayer(int awardForChain)
{
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
		int tetraminoCost = tetraminoInBoard->getTetraminoCost();
		award += (tetraminoCost + _prizeForChainConstant);
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
		tetraminoInBoard->setLivesToZero();
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
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
	int awardForChain = getAwardForChainForTetraminos(aTetraminos);
	function<void()> callback = [this, awardForChain](){
			addAwardToPlayer(awardForChain);
		};
	_delegate->setCallback(callback);
}