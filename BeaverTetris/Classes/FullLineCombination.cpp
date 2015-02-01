#include "FullLineCombination.h"
#include "GameBoard.h"
#include "CurrentPlayerDataSource.h"
#include "AwardForTetraminoDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "Tetramino.h"
#include "GameDesignConstants.h"

FullLineCombination::FullLineCombination(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
}


FullLineCombination::~FullLineCombination(void)
{
}

void FullLineCombination::checkFullLineCombination()
{
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	for (int yIndex = 0; yIndex < gameBoardHeight; yIndex++)
	{
		checkFullLineInBoardRow(yIndex);
	}
}

void FullLineCombination::checkFullLineInBoardRow(int aRow)
{
	if (fullLineCheck(aRow))
	{
		int playerAwardForLine = getPlayerAwardForLine(aRow);
		addAwardToPlayerScore(playerAwardForLine);
		removeKilledTetraminosFromBoardOnLine(aRow);
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

int FullLineCombination::getPlayerAwardForLine(int aIndex)
{
	int playerAwardForLine = 0;
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,aIndex);
		tetraminoInBoard->reduceLive();
		int award = getAwardForTetramino(tetraminoInBoard);
		playerAwardForLine += award;
	
	}
	return  playerAwardForLine;
}

int FullLineCombination::getAwardForTetramino(Tetramino *aTetramino)
{
	int award = 0;
	if (aTetramino->getTetraminoLivesCount() <= 0)
	{
		TetraminoType type = aTetramino->getTetraminoType();
		int awardForTetramino = _awardForTetraminoDataSource->getAwardForTetraminoType(type);
		award += awardForTetramino;
	}
	return award;
}

void FullLineCombination::addAwardToPlayerScore(int aAward)
{
	int playerAwardForLine = playerPrizeForLine + aAward;
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
	_currentPlayerDataSource->setPlayerScore(currentPlayerScore + playerAwardForLine);
}

void FullLineCombination::removeKilledTetraminosFromBoardOnLine(int aLine)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(widthIndex, aLine);
	}
}