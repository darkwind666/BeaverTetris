#include "CohesionSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "CohesionSpellDelegate.h"
#include "TetraminosFactory.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

CohesionSpell::CohesionSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
	_delegate = NULL;
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_cohesionCount = currentPlayerDataSource->getSpellCountForKey(cohesionSpellKey);
}

CohesionSpell::~CohesionSpell(void)
{
}

bool CohesionSpell::spellAvailable(void)
{
	return true;
}

void CohesionSpell::castSpell()
{
	srand(time(0));
	for (int emptyTetraminosIndex = 0; emptyTetraminosIndex < _cohesionCount; emptyTetraminosIndex++)
	{
		setNewTetraminoInBoard();
	}
}

void CohesionSpell::setNewTetraminoInBoard()
{
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	for (int heightIndex = 0; heightIndex < gameBoardHeight; heightIndex++)
	{
		if (availablePlaceForTetraminoInLine(heightIndex))
		{
			placeNewTetraminoInLine(heightIndex);
			break;
		}
	}
}

bool CohesionSpell::availablePlaceForTetraminoInLine(int aLine)
{
	bool availablePlace = false;
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < gameBoardWidth; widthIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aLine);
		if (tetraminoInBoard->getTetraminoType() == kTetraminoEmpty)
		{
			availablePlace = true;
			break;
		}
	}
	return availablePlace;
}

void CohesionSpell::placeNewTetraminoInLine(int aLine)
{
	int gameBoardWidth = _gameBoard->getGameBoardWidth();
	for (int widthIndex = 0; widthIndex < gameBoardWidth; widthIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aLine);
		if (tetraminoInBoard->getTetraminoType() == kTetraminoEmpty)
		{
			GamePositionOnBoard position;
			position.xPosition = widthIndex;
			position.yPosition = aLine;
			setNewTetraminoForPosition(position);
			sendMessageToDelegateWithTetraminoPosition(position);
			break;
		}
	}
}

void CohesionSpell::setNewTetraminoForPosition(GamePositionOnBoard aPosition)
{
	TetraminoType newTetraminoType = getRandomTetraminoType();
	Tetramino *newTetramino = _tetraminosFactory->getNewTetraminoWithType(newTetraminoType);
	_gameBoard->setTetraminoXYposition(newTetramino, aPosition.xPosition, aPosition.yPosition);
}

TetraminoType CohesionSpell::getRandomTetraminoType()
{
	TetraminoType newType = (TetraminoType)(GameHelper::getRandomNumberFromUpInterval(kTetraminoBlack) + kTetraminoRed);
	return newType;
}

void  CohesionSpell::setDelegate(CohesionSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}

void CohesionSpell::sendMessageToDelegateWithTetraminoPosition(GamePositionOnBoard aPosition)
{
	if (_delegate)
	{
		_delegate->makeTetraminoOnPosition(aPosition);
	}
}






