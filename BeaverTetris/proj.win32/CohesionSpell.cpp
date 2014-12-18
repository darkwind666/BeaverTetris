#include "CohesionSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"

using namespace std;

CohesionSpell::CohesionSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_someTetraminosWasRemoved = false;
}


CohesionSpell::~CohesionSpell(void)
{
}

bool CohesionSpell::spellAvailable(void)
{
	vector<GamePositionOnBoard> emptyTetraminosForCohesion = getEmptyTetraminosForCohesion();
	bool spellAvailable = true;

	if (emptyTetraminosForCohesion.size() < minEmptyTetraminoForCohesionCount)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void CohesionSpell::castSpell()
{
	vector<GamePositionOnBoard> emptyTetraminosForCohesion = getEmptyTetraminosForCohesion();

	int tetraminosSize = emptyTetraminosForCohesion.size();

	for (int emptyTetraminosIndex = 0; emptyTetraminosIndex <= tetraminosSize; emptyTetraminosIndex++)
	{
		int randomEmptyTetraminoIndex = GameHelper::getRandomNumberFromUpInterval(emptyTetraminosForCohesion.size());
		setNewTetraminoForIndexInEmptyTetraminos(randomEmptyTetraminoIndex, emptyTetraminosForCohesion);
		emptyTetraminosForCohesion.erase(emptyTetraminosForCohesion.begin() + randomEmptyTetraminoIndex);
	}

}



vector<GamePositionOnBoard> CohesionSpell::getEmptyTetraminosForCohesion()
{
	vector<GamePositionOnBoard> emptyTetraminosForCohesion;

	vector<GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	vector<GamePositionOnBoard>::iterator availableTetraminosIterator;

	for (availableTetraminosIterator = availableTetraminos.begin(); availableTetraminosIterator != availableTetraminos.end(); availableTetraminosIterator++)
	{
		vector<GamePositionOnBoard> emptyTetraminosPositionsAroundPosition = getEmptyTetraminosPositionsAroundPosition(*availableTetraminosIterator);
		setNewEmptyTetraminosInEmptyTetraminosForCohesion(emptyTetraminosPositionsAroundPosition, emptyTetraminosForCohesion);
	}
	return emptyTetraminosForCohesion;
}

vector<GamePositionOnBoard> CohesionSpell::getEmptyTetraminosPositionsAroundPosition(GamePositionOnBoard aPosition)
{
	vector<GamePositionOnBoard> tetraminosPositions = getTetraminosAroundPosition(aPosition);
	vector<GamePositionOnBoard> emptyTetraminosPositionsWithoutBorder = getEmptyTetraminosPositionsWithoutBorder(tetraminosPositions);
	return emptyTetraminosPositionsWithoutBorder;
}

vector<GamePositionOnBoard> CohesionSpell::getTetraminosAroundPosition(GamePositionOnBoard aPosition)
{
	vector<GamePositionOnBoard> emptyTetraminosPositions;
	
	GamePositionOnBoard positionLeft = aPosition;
	positionLeft.xPosition = aPosition.xPosition - 1;
	
	GamePositionOnBoard positionRight = aPosition;
	positionRight.xPosition = aPosition.xPosition + 1;
	
	GamePositionOnBoard positionUp = aPosition;
	positionUp.yPosition = aPosition.yPosition + 1;
	
	GamePositionOnBoard positionDown = aPosition;
	positionDown.yPosition = aPosition.yPosition - 1;
	
	emptyTetraminosPositions.push_back(positionLeft);
	emptyTetraminosPositions.push_back(positionRight);
	emptyTetraminosPositions.push_back(positionUp);
	emptyTetraminosPositions.push_back(positionDown);

	return emptyTetraminosPositions;
}

vector<GamePositionOnBoard> CohesionSpell::getEmptyTetraminosPositionsWithoutBorder(vector<GamePositionOnBoard> emptyTetraminosPositions)
{
	vector<GamePositionOnBoard> emptyTetraminosPositionsWithoutBorder;

	vector<GamePositionOnBoard>::iterator emptyTetraminosPositionsIterator;

	for (emptyTetraminosPositionsIterator = emptyTetraminosPositions.begin(); emptyTetraminosPositionsIterator != emptyTetraminosPositions.end(); emptyTetraminosPositionsIterator++)
	{
		GamePositionOnBoard positionInBoard = *emptyTetraminosPositionsIterator;
		bool inWidthBorder = (positionInBoard.xPosition >= 0 && positionInBoard.xPosition <= _gameBoard->getGameBoardWidth());
		bool inHeightBorder = (positionInBoard.yPosition >= 0 && positionInBoard.yPosition <= _gameBoard->getGameBoardHeight());

		if (inWidthBorder && inHeightBorder)
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(positionInBoard.xPosition, positionInBoard.yPosition);
			if (tetraminoInBoard->getTetraminoType() == kTetraminoEmpty)
			{
				emptyTetraminosPositionsWithoutBorder.push_back(positionInBoard);
			}

		}

	}
	return emptyTetraminosPositionsWithoutBorder;
}

void CohesionSpell::setNewEmptyTetraminosInEmptyTetraminosForCohesion(vector<GamePositionOnBoard> &newEmptyTetraminosPositions, vector<GamePositionOnBoard> &emptyTetraminosForCohesion)
{

	vector<GamePositionOnBoard>::iterator newEmptyTetraminosIterator;
	for (newEmptyTetraminosIterator = newEmptyTetraminosPositions.begin(); newEmptyTetraminosIterator != newEmptyTetraminosPositions.end(); newEmptyTetraminosIterator++)
	{
		GamePositionOnBoard newTetraminoPosition = *newEmptyTetraminosIterator;
		setNewEmptyTetraminoInEmptyTetraminos(newTetraminoPosition, emptyTetraminosForCohesion);

	}

}

void CohesionSpell::setNewEmptyTetraminoInEmptyTetraminos(GamePositionOnBoard newTetraminoPosition, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion)
{
	Tetramino *newTetramino = _gameBoard->getTetraminoForXYposition(newTetraminoPosition.xPosition, newTetraminoPosition.yPosition);
	
	vector<GamePositionOnBoard>::iterator emptyTetraminosForCohesionIterator;
	for (emptyTetraminosForCohesionIterator = emptyTetraminosForCohesion.begin(); emptyTetraminosForCohesionIterator < emptyTetraminosForCohesion.end(); emptyTetraminosForCohesionIterator++)
	{
		GamePositionOnBoard oldTetraminoPosition = *emptyTetraminosForCohesionIterator;
		Tetramino *oldTetramino = _gameBoard->getTetraminoForXYposition(oldTetraminoPosition.xPosition, oldTetraminoPosition.yPosition);
	
		if (newTetramino != oldTetramino)
		{
			emptyTetraminosForCohesion.push_back(newTetraminoPosition);
			break;
		}
	
	}
}

void CohesionSpell::setNewTetraminoForIndexInEmptyTetraminos(int tetraminoIndex, std::vector<GamePositionOnBoard> &emptyTetraminosForCohesion)
{
	GamePositionOnBoard emptyTetraminoPosition = emptyTetraminosForCohesion[tetraminoIndex];
	TetraminoType newTetraminoType = getRandomTetraminoType();
	Tetramino *newTetramino = new Tetramino(newTetraminoType);
	_gameBoard->setTetraminoXYposition(newTetramino, emptyTetraminoPosition.xPosition, emptyTetraminoPosition.yPosition);
}

TetraminoType CohesionSpell::getRandomTetraminoType()
{
	TetraminoType newType = (TetraminoType)(GameHelper::getRandomNumberFromUpInterval(kTetraminoBlack) + kTetraminoRed);
	return newType;
}