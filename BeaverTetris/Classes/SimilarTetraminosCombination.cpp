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
		checkChainInDetailElements(*detailsInGameIterator);
	}
}

void SimilarTetraminosCombination::checkChainInDetailElements(vector<GamePositionOnBoard> aTetraminos)
{
	checkChainInDetailHorisontals(aTetraminos);
	checkChainInDetailVerticals(aTetraminos);
}





void SimilarTetraminosCombination::checkChainInDetailHorisontals(vector<GamePositionOnBoard> aTetraminos)
{
	TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(aTetraminos);
	for (int yIndex = 0; yIndex < detailFromElements->getDetailHeight(); yIndex++)
	{
		vector<GamePositionOnBoard> chainElements = getChainInDetailHorisontal(detailFromElements, yIndex);
		if (chainElements.size() >= tetraminosInChainCount)
		{
			cleanChain(chainElements);
		}
	}
	delete detailFromElements;
}

vector<GamePositionOnBoard> SimilarTetraminosCombination::getChainInDetailHorisontal(TetraminoDetail *aDetail, int yPosition)
{
	vector<GamePositionOnBoard> tetraminosPositions;
	for (int xIndex = 0; xIndex < aDetail->getDetailWidth(); xIndex++)
	{
		GamePositionOnBoard positionInDetail;
		positionInDetail.xPosition = xIndex;
		positionInDetail.yPosition = yPosition;
		tetraminosPositions.push_back(positionInDetail);
	}
	vector<GamePositionOnBoard> chain = getChainFromTetraminosPositions(tetraminosPositions, aDetail);
	return chain;
}






vector<GamePositionOnBoard> SimilarTetraminosCombination::getChainFromTetraminosPositions(vector<GamePositionOnBoard> aPositions, TetraminoDetail *aDetail)
{
	vector< vector<GamePositionOnBoard> > chains;
	vector<GamePositionOnBoard> chain;
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aPositions.begin(); tetraminosIterator != aPositions.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		if (tetraminoInDetail->getTetraminoType() > kTetraminoEmpty)
		{
			GamePositionOnBoard absoluteTetraminoPosition = aDetail->convertPositionInDetailToAbsolutePosition(tetraminoPosition);
			chain.push_back(absoluteTetraminoPosition);
		}
		else
		{
			vector<GamePositionOnBoard> chainFromPositions = chain;
			chains.push_back(chainFromPositions);
			chain.clear();
		}
	}
	chains.push_back(chain);
	sortChains(chains);
	return chains[0];
}

void SimilarTetraminosCombination::sortChains(std::vector< std::vector<GamePositionOnBoard> > &aChains)
{
	sort(aChains.begin(), aChains.end(), [](vector<GamePositionOnBoard> &chainA, vector<GamePositionOnBoard> &chainB){
		return (chainA.size() > chainB.size());
	});
}







void SimilarTetraminosCombination::checkChainInDetailVerticals(vector<GamePositionOnBoard> aTetraminos)
{
	TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(aTetraminos);
	for (int xIndex = 0; xIndex < detailFromElements->getDetailWidth(); xIndex++)
	{
		vector<GamePositionOnBoard> chainElements = getChainInDetailVertical(detailFromElements, xIndex);
		if (chainElements.size() >= tetraminosInChainCount)
		{
			cleanChain(chainElements);
		}
	}
	delete detailFromElements;
}

vector<GamePositionOnBoard> SimilarTetraminosCombination::getChainInDetailVertical(TetraminoDetail *aDetail, int xPosition)
{
	vector<GamePositionOnBoard> tetraminosPositions;
	for (int yIndex = 0; yIndex < aDetail->getDetailHeight(); yIndex++)
	{
		GamePositionOnBoard positionInDetail;
		positionInDetail.xPosition = xPosition;
		positionInDetail.yPosition = yIndex;
		tetraminosPositions.push_back(positionInDetail);
	}
	vector<GamePositionOnBoard> chain = getChainFromTetraminosPositions(tetraminosPositions, aDetail);
	return chain;
}







void SimilarTetraminosCombination::cleanChain(vector<GamePositionOnBoard> aPositions)
{
	sendMassageToDelegateWithTetraminos(aPositions);
	setAwardToPlayerFromTetraminos(aPositions);
	removeTetraminosWithPositions(aPositions);
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