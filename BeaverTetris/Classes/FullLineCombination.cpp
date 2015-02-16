#include "FullLineCombination.h"
#include "GameBoard.h"
#include "CurrentPlayerDataSource.h"
#include "AwardForTetraminoDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "Tetramino.h"
#include "GameDesignConstants.h"
#include "ExplosionAnimationDelegate.h"

using namespace std;

FullLineCombination::FullLineCombination(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_awardForTetraminoDataSource = (AwardForTetraminoDataSource*)ServiceLocator::getServiceForKey(awardForTetraminoDataSourceKey);
	_delegate = NULL;
}

FullLineCombination::~FullLineCombination(void)
{
}

void FullLineCombination::setDelegate(ExplosionAnimationDelegate *aDelegate)
{
	_delegate = aDelegate;
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
		reduceTetraminosLifesInLine(aRow);
		sendMessagesToDelegateAccordingToLine(aRow);
		setUpPlayerScoreWithAwardFromLine(aRow);
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

void FullLineCombination::reduceTetraminosLifesInLine(int aLine)
{
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,aLine);
		tetraminoInBoard->reduceLive();
	}
}

void FullLineCombination::sendMessagesToDelegateAccordingToLine(int aLine)
{
	if (_delegate)
	{
		_delegate->blowUpLine(aLine);
		sendDelegateKilledTetraminosFromBoardOnLine(aLine);
		int playerAwardForLine = getPlayerAwardForLine(aLine);
		sendDelegatePlayerAward(playerAwardForLine);
	}
}

void FullLineCombination::setUpPlayerScoreWithAwardFromLine(int aLine)
{
	if (_delegate == NULL)
	{
		int playerAwardForLine = getPlayerAwardForLine(aLine);
		addAwardToPlayerScore(playerAwardForLine);
	}
}

int FullLineCombination::getPlayerAwardForLine(int aIndex)
{
	int playerAwardForLine = 0;
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xIndex,aIndex);
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
	int newPlayerScore = currentPlayerScore + playerAwardForLine;
	_currentPlayerDataSource->setPlayerScore(newPlayerScore);
}

void FullLineCombination::removeKilledTetraminosFromBoardOnLine(int aLine)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(widthIndex, aLine);
	}
}

void FullLineCombination::sendDelegateKilledTetraminosFromBoardOnLine(int aLine)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aLine);
		if (tetraminoInBoard->getTetraminoLivesCount() <= 0)
		{
			_delegate->removeTetraminoOnPositionXY(widthIndex, aLine);
		}
	}
}

void FullLineCombination::sendDelegatePlayerAward(int aPlayerAward)
{
	function<void()> callback = [this, aPlayerAward](){
			addAwardToPlayerScore(aPlayerAward);
		};
	_delegate->setCallback(callback);
}