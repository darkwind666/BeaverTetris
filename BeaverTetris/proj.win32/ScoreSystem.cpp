#include "ScoreSystem.h"
#include "GameDesignConstants.h"


ScoreSystem::ScoreSystem(AwardForTetraminoDataSource *aAwardForTetraminoDataSource, GameBoard *aGameBoard, CurrentPlayerDataSource *aCurrentPlayerDataSource, TetraminosSeparatorDelegate *aTetraminosSeparatorDelegate)
{
	_awardForTetraminoDataSource = aAwardForTetraminoDataSource;
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = aCurrentPlayerDataSource;
	_someObjectWasDeletedIndicator = false;
	_tetraminosSeparatorDelegate = aTetraminosSeparatorDelegate;
}


ScoreSystem::~ScoreSystem(void)
{
}

void ScoreSystem::updateSystem(float deltaTime)
{

	for (int yIndex = 0; yIndex < _gameBoard->getGameBoardHeight; yIndex++)
	{

		if (fullLineCheck(yIndex))
		{

			int playerAwardForLine;

			for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth; xIndex++)
			{
				Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,yIndex);
				tetraminoInBoard->reduceLive();
				int award = getAwardForTetramino(tetraminoInBoard);
				playerAwardForLine += award;

			}

			removeKilledTetraminos(yIndex);

			playerAwardForLine += playerPrizeForLine;
			int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
			_currentPlayerDataSource->setPlayerScore(currentPlayerScore + playerAwardForLine);

		}

	}

	if (_someObjectWasDeletedIndicator)
	{
		_tetraminosSeparatorDelegate->separateTetraminos();
		_someObjectWasDeletedIndicator = false;
	}

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

void ScoreSystem::removeKilledTetraminos(int lineIndex)
{
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth; xIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,lineIndex);
	
		if (tetraminoInBoard->getTetraminoLivesCount <= 0)
		{
			_gameBoard->removeTetraminoForXYposition(xIndex,lineIndex);
			_someObjectWasDeletedIndicator = true;
		}
	
	}
}