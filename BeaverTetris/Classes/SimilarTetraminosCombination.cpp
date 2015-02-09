#include "SimilarTetraminosCombination.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "TetraminoDetail.h"
#include "CurrentPlayerDataSource.h"
#include "AwardForTetraminoDataSource.h"
#include "TetraminosCombinatorDelegate.h"
#include "DetailsFromBoardDataSource.h"
#include "GameDesignConstants.h"
#include "SimilarTetraminosCombinationDelegate.h"

using namespace std;

SimilarTetraminosCombination::SimilarTetraminosCombination(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
	_delegate = NULL;
}


SimilarTetraminosCombination::~SimilarTetraminosCombination(void)
{
	delete _detailsFromBoardDataSource;
	delete _tetraminosCombinatorDelegate;
}

void SimilarTetraminosCombination::checkSimilarTetraminosCombination()
{
	vector < vector <GamePositionOnBoard> > detailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame();
	vector < vector <GamePositionOnBoard> >::iterator detailsInGameIterator;
	for (detailsInGameIterator = detailsInGame.begin(); detailsInGameIterator != detailsInGame.end(); detailsInGameIterator++)
	{
		TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(*detailsInGameIterator);
		if (checkChainInDetail(detailFromElements))
		{
			sendMassageToDelegateWithTetraminos(*detailsInGameIterator);
			setAwardToPlayerFromTetraminos(*detailsInGameIterator);
			removeTetraminosWithPositions(*detailsInGameIterator);
		}
		delete detailFromElements;
	}
}

bool SimilarTetraminosCombination::checkChainInDetail(TetraminoDetail *aDetail)
{
	bool chainInHorizontal = checkChainInDetailHorisontals(aDetail);
	bool chainInVertical = checkChainInDetailVerticals(aDetail);
	return (chainInHorizontal == true || chainInVertical == true);
}

bool SimilarTetraminosCombination::checkChainInDetailHorisontals(TetraminoDetail *aDetail)
{
	bool chain = false;
	for (int yIndex = 0; yIndex < aDetail->getDetailHeight(); yIndex++)
	{
		int chainCountInHorisontal = getChainInDetailHorisontal(aDetail, yIndex);
		if (chainCountInHorisontal >= tetraminosInChainCount)
		{
			chain = true;
			break;
		}
	}
	return chain;
}

int SimilarTetraminosCombination::getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition)
{
	vector<Tetramino*> tetraminos;
	for (int xIndex = 0; xIndex < aDetail->getDetailWidth(); xIndex++)
	{
		Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xIndex, yPosition);
		tetraminos.push_back(tetraminoInDetail);
	}
	int chainCount = getChainCountFromTetraminos(tetraminos);
	return chainCount;
}

int SimilarTetraminosCombination::getChainCountFromTetraminos(vector<Tetramino*> aTetraminos)
{
	int maxChainCount = 0;
	int chainCount = 0;
	vector<Tetramino*>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		Tetramino *tetraminoInDetail = *tetraminosIterator;
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			chainCount++;
			if (chainCount > maxChainCount)
			{
				maxChainCount = chainCount;
			}
		}
		else
		{
			chainCount = 0;
		}
	}
	return maxChainCount;
}

bool SimilarTetraminosCombination::checkChainInDetailVerticals(TetraminoDetail *aDetail)
{
	bool chain = false;
	for (int xIndex = 0; xIndex < aDetail->getDetailWidth(); xIndex++)
	{
		int chainCountInHorisontal = getChainInDetailVertical(aDetail, xIndex);
		if (chainCountInHorisontal >= tetraminosInChainCount)
		{
			chain = true;
			break;
		}
	}
	return chain;
}

int SimilarTetraminosCombination::getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition)
{
	vector<Tetramino*> tetraminos;
	for (int yIndex = 0; yIndex < aDetail->getDetailHeight(); yIndex++)
	{
		Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xPosition, yIndex);
		tetraminos.push_back(tetraminoInDetail);
	}
	int chainCount = getChainCountFromTetraminos(tetraminos);
	return chainCount;
}

void SimilarTetraminosCombination::setAwardToPlayerFromTetraminos(vector<GamePositionOnBoard> aTetraminos)
{
	if (_delegate == NULL)
	{
		setTetraminosAward(aTetraminos);
	}
}

void SimilarTetraminosCombination::setTetraminosAward(std::vector<GamePositionOnBoard> aTetraminos)
{
	int awardForChain = getAwardForChainForTetraminos(aTetraminos);
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
	_currentPlayerDataSource->setPlayerScore(currentPlayerScore + awardForChain);
}

int SimilarTetraminosCombination::getAwardForChainForTetraminos(vector<GamePositionOnBoard> aTetraminos)
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

void SimilarTetraminosCombination::removeTetraminosWithPositions(vector<GamePositionOnBoard> aTetraminos)
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

void SimilarTetraminosCombination::setDelegate(SimilarTetraminosCombinationDelegate *aDelegate)
{
	_delegate = aDelegate;
}

void SimilarTetraminosCombination::sendMassageToDelegateWithTetraminos(vector<GamePositionOnBoard> aTetraminos)
{
	if (_delegate)
	{
		_delegate->blowUpTetraminosForPositions(aTetraminos);
		sendRemoveTetraminosMassagesToDelegate(aTetraminos);
		sendCallbackWithAwardForTetraminosToDelegate(aTetraminos);
	}
}

void SimilarTetraminosCombination::sendRemoveTetraminosMassagesToDelegate(vector<GamePositionOnBoard> aTetraminos)
{
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		_delegate->removeTetraminoOnPositionXY(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
	}
}

void SimilarTetraminosCombination::sendCallbackWithAwardForTetraminosToDelegate(vector<GamePositionOnBoard> aTetraminos)
{
	function<void()> callback = [this, aTetraminos](){
			setTetraminosAward(aTetraminos);
		};
	_delegate->setCallback(callback);
}