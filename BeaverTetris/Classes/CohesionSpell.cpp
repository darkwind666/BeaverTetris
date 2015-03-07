#include "CohesionSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "CohesionSpellDelegate.h"
#include "TetraminosFactory.h"

using namespace std;

CohesionSpell::CohesionSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_tetraminosFactory = (TetraminosFactory*)ServiceLocator::getServiceForKey(tetrominosFactoryKey);
	_delegate = NULL;
}

CohesionSpell::~CohesionSpell(void)
{
}

bool CohesionSpell::spellAvailable(void)
{
	bool spellAvailable = true;
	vector<GamePositionOnBoard> emptyTetraminosForCohesion = getEmptyTetraminosForCohesion();
	if (emptyTetraminosForCohesion.size() < minEmptyTetraminoForCohesionCount)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void CohesionSpell::castSpell()
{
	srand(time(0));
	vector<GamePositionOnBoard> emptyTetraminosForCohesion = getEmptyTetraminosForCohesion();
	for (int emptyTetraminosIndex = 0; emptyTetraminosIndex < cohesionCount; emptyTetraminosIndex++)
	{
		int randomEmptyTetraminoIndex = GameHelper::getRandomNumberFromUpInterval(emptyTetraminosForCohesion.size());
		GamePositionOnBoard emptyTetraminoPosition = emptyTetraminosForCohesion[randomEmptyTetraminoIndex];
		setNewTetraminoForPosition(emptyTetraminoPosition);
		sendMessageToDelegateWithTetraminoPosition(emptyTetraminoPosition);
		emptyTetraminosForCohesion.erase(emptyTetraminosForCohesion.begin() + randomEmptyTetraminoIndex);
	}
}

vector<GamePositionOnBoard> CohesionSpell::getEmptyTetraminosForCohesion()
{
	vector<GamePositionOnBoard> emptyTetraminosForCohesion;
	vector<GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = availableTetraminos.begin(); tetraminosIterator != availableTetraminos.end(); tetraminosIterator++)
	{
		vector<GamePositionOnBoard> emptyTetraminosAroundPosition = getEmptyTetraminosPositionsAroundPosition(*tetraminosIterator);
		setTetraminosInTetraminosForCohesion(emptyTetraminosAroundPosition, emptyTetraminosForCohesion);
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

vector<GamePositionOnBoard> CohesionSpell::getEmptyTetraminosPositionsWithoutBorder(vector<GamePositionOnBoard> tetraminosPositions)
{
	vector<GamePositionOnBoard> emptyTetraminosPositionsWithoutBorder;
	vector<GamePositionOnBoard>::iterator positionsIterator;
	for (positionsIterator = tetraminosPositions.begin(); positionsIterator != tetraminosPositions.end(); positionsIterator++)
	{
		GamePositionOnBoard positionInBoard = *positionsIterator;
		if (_gameBoard->positionInBoard(positionInBoard))
		{
			setTetraminoPositionInPositions(positionInBoard, emptyTetraminosPositionsWithoutBorder);
		}
	}
	return emptyTetraminosPositionsWithoutBorder;
}

void CohesionSpell::setTetraminoPositionInPositions(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &tetraminosPositions)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	if (tetraminoInBoard->getTetraminoType() == kTetraminoEmpty)
	{
		tetraminosPositions.push_back(aPosition);
	}
}

void CohesionSpell::setTetraminosInTetraminosForCohesion(vector<GamePositionOnBoard> &tetraminosPositions, vector<GamePositionOnBoard> &tetraminosForCohesion)
{
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = tetraminosPositions.begin(); tetraminosIterator != tetraminosPositions.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		setPositionInTetraminosForCohesion(tetraminoPosition, tetraminosForCohesion);
	}
}

void CohesionSpell::setPositionInTetraminosForCohesion(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &tetraminosForCohesion)
{
	if (tetraminosForCohesion.size() > 0)
	{
		setTetraminoPositionInTetraminosForCohesion(aPosition, tetraminosForCohesion);
	}
	else
	{
		tetraminosForCohesion.push_back(aPosition);
	}
}

void CohesionSpell::setTetraminoPositionInTetraminosForCohesion(GamePositionOnBoard aPosition, vector<GamePositionOnBoard> &tetraminosForCohesion)
{
	bool tetraminoInCollection = checkTetraminoPositionInPositions(aPosition, tetraminosForCohesion);
	if (tetraminoInCollection == false)
	{
		tetraminosForCohesion.push_back(aPosition);
	}
}

bool CohesionSpell::checkTetraminoPositionInPositions(GamePositionOnBoard aPosition, std::vector<GamePositionOnBoard> &aPositions)
{
	bool tetraminoInCollection = false;
	Tetramino *newTetamino = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aPositions.begin(); tetraminosIterator != aPositions.end(); tetraminosIterator++)
	{
		GamePositionOnBoard oldTetraminoPosition = *tetraminosIterator;
		Tetramino *oldTetramino = _gameBoard->getTetraminoForXYposition(oldTetraminoPosition.xPosition, oldTetraminoPosition.yPosition);
		if (newTetamino == oldTetramino)
		{
			tetraminoInCollection = true;
			break;
		}
	}
	return tetraminoInCollection;
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