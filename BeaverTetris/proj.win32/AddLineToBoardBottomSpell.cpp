#include "AddLineToBoardBottomSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "ActiveDetails.h"
#include "GameEnums.h"

using namespace std;

AddLineToBoardBottomSpell::AddLineToBoardBottomSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
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
}

void AddLineToBoardBottomSpell::riseAllTetraminos()
{
	vector <GamePositionOnBoard> allAvailableTetraminos = _gameBoard->getAvailableTetraminis();

	vector <GamePositionOnBoard>::reverse_iterator allAvailableTetraminosIterator;
	for (allAvailableTetraminosIterator = allAvailableTetraminos.rbegin(); allAvailableTetraminosIterator != allAvailableTetraminos.rend(); allAvailableTetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *allAvailableTetraminosIterator;
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		GamePositionOnBoard newTetraminoPosition = tetraminoPosition;
		newTetraminoPosition.yPosition = newTetraminoPosition.yPosition + 1;

		if (newTetraminoPosition.yPosition > _gameBoard->getGameBoardHeight())
		{
			_gameBoard->removeTetraminoForXYposition(newTetraminoPosition.xPosition, newTetraminoPosition.yPosition);
		}
		else
		{
			_gameBoard->setTetraminoXYposition(tetraminoInBoard, newTetraminoPosition.xPosition, newTetraminoPosition.yPosition);
		}

	}

}

void AddLineToBoardBottomSpell::addRowToBottom()
{
	for (int widthIndex = 0; widthIndex <= _gameBoard->getGameBoardWidth(); widthIndex++)
	{
		TetraminoType randomTetraminoType = (TetraminoType)GameHelper::getRandomNumberFromUpInterval(kTetraminoBossQueen);
		Tetramino *newTetramino = new Tetramino(randomTetraminoType);
		_gameBoard->setTetraminoXYposition(newTetramino, widthIndex, 0);
	}
}

bool AddLineToBoardBottomSpell::checkEmptyTetraminosInBottom()
{
	bool emptyTetramino = false;

	for (int widthIndex = 0; widthIndex <= _gameBoard->getGameBoardWidth(); widthIndex++)
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