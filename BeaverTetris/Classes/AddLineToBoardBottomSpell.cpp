#include "AddLineToBoardBottomSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameBoard.h"
#include "GameHelper.h"
#include "Tetramino.h"
#include "GameEnums.h"
#include "AddLineToBoardBottomSpellDelegate.h"
#include "TetraminosFactory.h"

using namespace std;

AddLineToBoardBottomSpell::AddLineToBoardBottomSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
	_tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
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
	sendUpGameBoardMessageToDelegate();
	riseAllTetraminos();
	addRowToBottom();
	sendAddLineMessageToDelegate();
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
		TetraminoType randomTetraminoType = getTetraminoTypeForXPosition(widthIndex);
		Tetramino *newTetramino = _tetraminosFactory->getNewTetraminoWithType(randomTetraminoType);
		_gameBoard->setTetraminoXYposition(newTetramino, widthIndex, 0);
	}
}

TetraminoType AddLineToBoardBottomSpell::getTetraminoTypeForXPosition(int xPosition)
{
	TetraminoType randomTetraminoType = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, 1);
	TetraminoType tetraminoInBoardType = tetraminoInBoard->getTetraminoType();
	while (tetraminoInBoardType == randomTetraminoType && tetraminoInBoardType != kTetraminoEmpty)
	{
		randomTetraminoType = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
	}
	return randomTetraminoType;
}

void AddLineToBoardBottomSpell::makeGapInBottom()
{
	int boardWidth = _gameBoard->getGameBoardWidth();
	if (checkEmptyTetraminosInBottom() == false)
	{
		Tetramino *emptyTetramino = _tetraminosFactory->getNewTetraminoWithType(kTetraminoEmpty);
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

void AddLineToBoardBottomSpell::sendUpGameBoardMessageToDelegate()
{
	if (_delegate)
	{
		_delegate->upGameBoard();
	}
}

void AddLineToBoardBottomSpell::sendAddLineMessageToDelegate()
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

void AddLineToBoardBottomSpell::updateSpell()
{
	
}

float AddLineToBoardBottomSpell::getSpellRechargePercent()
{
	return 0.0f;
}