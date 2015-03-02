#include "AddLineToBoardBottomSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameBoard.h"
#include "GameHelper.h"
#include "Tetramino.h"
#include "GameEnums.h"
#include "AddLineToBoardBottomSpellDelegate.h"

using namespace std;

AddLineToBoardBottomSpell::AddLineToBoardBottomSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
}


AddLineToBoardBottomSpell::~AddLineToBoardBottomSpell(void)
{
}

bool AddLineToBoardBottomSpell::spellAvailable(void)
{
	return true;
}

void AddLineToBoardBottomSpell::castSpell()
{
	riseAllTetraminos();
	addRowToBottom();
	sendMessageToDelegate();
}

void AddLineToBoardBottomSpell::riseAllTetraminos()
{
	int boardHeight = _gameBoard->getGameBoardHeight();
	for (int heightIndex = boardHeight - 1; heightIndex >= 0; heightIndex--)
	{
		riseTetraminosLineInBoard(heightIndex);
	}
}

void AddLineToBoardBottomSpell::riseTetraminosLineInBoard(int aLineIndex)
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		riseTetraminoInBoardOnXY(widthIndex, aLineIndex);
	}
}

void AddLineToBoardBottomSpell::riseTetraminoInBoardOnXY(int xPosition, int yPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, yPosition);
	int newYposition = yPosition + 1;
	if (newYposition >= _gameBoard->getGameBoardHeight())
	{
		delete tetraminoInBoard;
	}
	else
	{
		_gameBoard->setTetraminoXYposition(tetraminoInBoard, xPosition, newYposition);
	}
}

void AddLineToBoardBottomSpell::addRowToBottom()
{
	fillBottomWithRandomTetraminos();
	makeGapInBottom();
}

void  AddLineToBoardBottomSpell::fillBottomWithRandomTetraminos()
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < boardWidth; widthIndex++)
	{
		TetraminoType randomTetraminoType = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
		Tetramino *newTetramino = new Tetramino(randomTetraminoType);
		_gameBoard->setTetraminoXYposition(newTetramino, widthIndex, 0);
	}
}

void AddLineToBoardBottomSpell::makeGapInBottom()
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	if (checkEmptyTetraminosInBottom() == false)
	{
		Tetramino *emptyTetramino = new Tetramino(kTetraminoEmpty);
		int randomIndex = GameHelper::getRandomNumberFromUpInterval(boardWidth);
		_gameBoard->replaceTetraminoXYposition(emptyTetramino, randomIndex, 0);
	}
}

bool AddLineToBoardBottomSpell::checkEmptyTetraminosInBottom()
{
	bool emptyTetramino = false;
	for (int widthIndex = 0; widthIndex < _gameBoard->getGameBoardWidth(); widthIndex++)
	{
		Tetramino *tetraminoInGameBoard = _gameBoard->getTetraminoForXYposition(widthIndex, 0);
		if (tetraminoInGameBoard->getTetraminoType() == kTetraminoEmpty)
		{
			emptyTetramino = true;
			break;
		}
	}
	return emptyTetramino;
}

void AddLineToBoardBottomSpell::sendMessageToDelegate()
{
	if (_delegate)
	{
		_delegate->addLineToGameBoard();
	}
}

void AddLineToBoardBottomSpell::setDelegate(AddLineToBoardBottomSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}