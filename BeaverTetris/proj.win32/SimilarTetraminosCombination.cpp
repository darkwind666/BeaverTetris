#include "SimilarTetraminosCombination.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

SimilarTetraminosCombination::SimilarTetraminosCombination(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource)
{
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);
}


SimilarTetraminosCombination::~SimilarTetraminosCombination(void)
{
}

void SimilarTetraminosCombination::checkSimilarTetraminosCombination()
{
	vector < vector <GamePositionOnBoard> > detailsInGame = _detailsFromBoardDataSource->getTetraminoDetailsInGame;
	
	vector < vector <GamePositionOnBoard> >::iterator detailsInGameIterator;
	
	for (detailsInGameIterator = detailsInGame.begin; detailsInGameIterator != detailsInGame.end; detailsInGameIterator++)
	{
		TetraminoDetail *detailFromElements = _tetraminosCombinatorDelegate->combineTetraminosInDetail(*detailsInGameIterator);
		if (checkChainInDetail(detailFromElements))
		{
			int awardForChain = getAwardForChainForTetraminos(*detailsInGameIterator);
			int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
			_currentPlayerDataSource->setPlayerScore(currentPlayerScore + awardForChain);
		}
	
	}
}

bool SimilarTetraminosCombination::checkChainInDetail(TetraminoDetail *aDetail)
{
	bool chainInHorizontal = checkChainInDetailHorisontals(aDetail);
	bool chainInVertical = checkChainInDetailVerticals(aDetail);
	return (chainInHorizontal || chainInVertical);
}

bool SimilarTetraminosCombination::checkChainInDetailHorisontals(TetraminoDetail *aDetail)
{
	bool chain = false;
	int chainCount = 0;

	for (int yIndex = 0; yIndex < aDetail->getDetailHeight; yIndex++)
	{
	
		for (int xIndex = 0; xIndex < aDetail->getDetailWidth; xIndex++)
		{
			Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xIndex, yIndex);
			if (tetraminoInDetail->getTetraminoType > kTetraminoEmpty)
			{
				chainCount++;
				if (chainCount >= tetraminosInChainCount)
				{
					chain = true;
					return chain;
				}
				else
				{
					chainCount = 0;
				}
	
			}
		}
		chainCount = 0;
	}
	return chain;
}

bool SimilarTetraminosCombination::checkChainInDetailVerticals(TetraminoDetail *aDetail)
{
	bool chain = false;
	int chainCount = 0;
	
	for (int xIndex = 0; xIndex < aDetail->getDetailWidth; xIndex++)
	{
	
		for (int yIndex = 0; yIndex < aDetail->getDetailHeight; yIndex++)
		{
			Tetramino *tetraminoInDetail = aDetail->getTetraminoForXY(xIndex, yIndex);
			if (tetraminoInDetail->getTetraminoType > kTetraminoEmpty)
			{
				chainCount++;
				if (chainCount >= tetraminosInChainCount)
				{
					chain = true;
					return chain;
				}
				else
				{
					chainCount = 0;
				}
	
			}
		}
		chainCount = 0;
	}
	return chain;
}

int SimilarTetraminosCombination::getAwardForChainForTetraminos(vector<GamePositionOnBoard> aTetraminos)
{

	int award = 0;

	vector<GamePositionOnBoard>::iterator tetraminosIterator;

	for (tetraminosIterator = aTetraminos.begin; tetraminosIterator != aTetraminos.end; tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition,tetraminoPosition.yPosition);
		award += (_awardForTetraminoDataSource->getAwardForTetraminoType(tetraminoInBoard->getTetraminoType)) + prizeForChainConstant;
	}
	return award;
}