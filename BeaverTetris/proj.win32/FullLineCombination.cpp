#include "FullLineCombination.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

FullLineCombination::FullLineCombination(GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource)
{
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
}


FullLineCombination::~FullLineCombination(void)
{
}

void FullLineCombination::checkFullLineCombination()
{
	for (int yIndex = 0; yIndex < _gameBoard->getGameBoardHeight(); yIndex++)
	{
	
		if (fullLineCheck(yIndex))
		{
	
			int playerAwardForLine;
	
			for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
			{
				Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,yIndex);
				tetraminoInBoard->reduceLive();
				int award = getAwardForTetramino(tetraminoInBoard);
				playerAwardForLine += award;
	
			}
	
			playerAwardForLine += playerPrizeForLine;
			int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
			_currentPlayerDataSource->setPlayerScore(currentPlayerScore + playerAwardForLine);
	
		}
	
	}
}

bool FullLineCombination::fullLineCheck(int lineIndex)
{
	bool fullLine = true;

		for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,lineIndex);

			if (tetraminoInBoard->getTetraminoType() <= kTetraminoEmpty)
			{
				fullLine = false;
				break;
			}

		}
		return fullLine;
}

int FullLineCombination::getAwardForTetramino(Tetramino *aTetramino)
{

	int award = 0;

	if (aTetramino->getTetraminoLivesCount() <= 0)
	{
		award += _awardForTetraminoDataSource->getAwardForTetraminoType(aTetramino->getTetraminoType());
	}

	return award;

}