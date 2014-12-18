#include "ScoreSystem.h"
#include "GameDesignConstants.h"

using namespace std;

ScoreSystem::ScoreSystem(AwardForTetraminoDataSource *aAwardForTetraminoDataSource, GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource)
{
	_awardForTetraminoDataSource = aAwardForTetraminoDataSource;
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_detailsFromBoardDataSource = new DetailsFromBoardDataSource(aGameBoard);
	_tetraminosCombinatorDelegate = new TetraminosCombinatorDelegate(aGameBoard);


	_fullLineCombination = new FullLineCombination(aGameBoard,aCurrentPlayerDataSource);

}


ScoreSystem::~ScoreSystem(void)
{
}

void ScoreSystem::updateSystem(float deltaTime)
{

	_fullLineCombination->checkFullLineCombination;
	checkTetraminoChains();

}

void ScoreSystem::checkTetraminoChains()
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

bool ScoreSystem::checkChainInDetail(TetraminoDetail *aDetail)
{
	bool chainInHorizontal = checkChainInDetailHorisontals(aDetail);
	bool chainInVertical = checkChainInDetailVerticals(aDetail);
	return (chainInHorizontal || chainInVertical);
}

bool ScoreSystem::checkChainInDetailHorisontals(TetraminoDetail *aDetail)
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

bool ScoreSystem::checkChainInDetailVerticals(TetraminoDetail *aDetail)
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

int ScoreSystem::getAwardForChainForTetraminos(vector<GamePositionOnBoard> aTetraminos)
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




bool ScoreSystem::fullLineCheck(int lineIndex)
{
	bool fullLine = true;

		for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth; xIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,lineIndex);

			if (tetraminoInBoard->getTetraminoType <= kTetraminoEmpty)
			{
				fullLine = false;
				break;
			}

		}
		return fullLine;
}

int ScoreSystem::getAwardForTetramino(Tetramino *aTetramino)
{

	int award = 0;

	if (aTetramino->getTetraminoLivesCount <= 0)
	{
		award += _awardForTetraminoDataSource->getAwardForTetraminoType(aTetramino->getTetraminoType);
	}

	return award;

}