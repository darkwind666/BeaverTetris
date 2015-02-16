#include "DamageToPlayerSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "GameEnums.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "ExplosionAnimationDelegate.h"

using namespace std;

DamageToPlayerSpell::DamageToPlayerSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
}


DamageToPlayerSpell::~DamageToPlayerSpell(void)
{
}

bool DamageToPlayerSpell::spellAvailable(void)
{
	bool spellAvailable = true;
	vector<int> linesWithUnpeacefulCount = getLinesWithUnpeacefulCount();
	if (linesWithUnpeacefulCount.size() <= 0)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

vector<int> DamageToPlayerSpell::getLinesWithUnpeacefulCount()
{
	vector<int> linesWithUnpeacefulCount;
	for (int heightIndex = 0; heightIndex < _gameBoard->getGameBoardHeight(); heightIndex++)
	{
		vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos = getUnEmptyAndNoBossesTetraminosInLine(heightIndex);
		if (unEmptyAndNoBossesTetraminos.size() > minPeacefulNonEmptyTetraminosCount)
		{
			linesWithUnpeacefulCount.push_back(heightIndex);
		}
	}
	return linesWithUnpeacefulCount;
}

vector<GamePositionOnBoard> DamageToPlayerSpell::getUnEmptyAndNoBossesTetraminosInLine(int aLine)
{
	vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos;
	for (int widthIndex = 0; widthIndex < _gameBoard->getGameBoardWidth(); widthIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aLine);
		if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty && tetraminoInBoard->getTetraminoType() < kTetraminoBossQueen)
		{
			GamePositionOnBoard tetraminoInBoardPosition;
			tetraminoInBoardPosition.xPosition = widthIndex;
			tetraminoInBoardPosition.yPosition = aLine;
			unEmptyAndNoBossesTetraminos.push_back(tetraminoInBoardPosition);
		}
	}
	return unEmptyAndNoBossesTetraminos;
}

void DamageToPlayerSpell::castSpell()
{
	vector<int> linesWithUnpeacefulCount = getLinesWithUnpeacefulCount();
	vector<GamePositionOnBoard> tetraminosForRemoving = getTetraminosForRemovingInLines(linesWithUnpeacefulCount);
	sendMessagesToDelegateWithTetraminosPositions(tetraminosForRemoving);
	removeTetramninos(tetraminosForRemoving);
}

vector<GamePositionOnBoard> DamageToPlayerSpell::getTetraminosForRemovingInLines(std::vector<int> aLines)
{
	vector<GamePositionOnBoard> tetraminosForRemoving;
	vector<int>::iterator linesIterator;
	for (linesIterator = aLines.begin(); linesIterator != aLines.end(); linesIterator++)
	{
		fillTetraminosRemovingWithTetraminosFromLine(tetraminosForRemoving, *linesIterator);
	}
	return tetraminosForRemoving;
}

void DamageToPlayerSpell::fillTetraminosRemovingWithTetraminosFromLine(vector<GamePositionOnBoard> &aPositions, int aLine)
{
	vector<GamePositionOnBoard> tetraminos = getTetraminosForRemovingInLine(aLine);
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = tetraminos.begin(); tetraminosIterator != tetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		aPositions.push_back(tetraminoPosition);
	}
}

vector<GamePositionOnBoard> DamageToPlayerSpell::getTetraminosForRemovingInLine(int aLine)
{
	vector<GamePositionOnBoard> tetraminos;
	vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos = getUnEmptyAndNoBossesTetraminosInLine(aLine);
	int reductionCount = unEmptyAndNoBossesTetraminos.size() - minPeacefulNonEmptyTetraminosCount;
	for (int reductionIndex = 0; reductionIndex <= reductionCount; reductionIndex++)
	{
		int reductionElementIndex = GameHelper::getRandomNumberFromUpInterval(unEmptyAndNoBossesTetraminos.size());
		GamePositionOnBoard tetraminoPosition = unEmptyAndNoBossesTetraminos[reductionElementIndex];
		tetraminos.push_back(tetraminoPosition);
		unEmptyAndNoBossesTetraminos.erase(unEmptyAndNoBossesTetraminos.begin() + reductionElementIndex);
	}
	return tetraminos;
}

void DamageToPlayerSpell::sendMessagesToDelegateWithTetraminosPositions(std::vector<GamePositionOnBoard> aPositions)
{
	if (_delegate)
	{
		_delegate->blowUpTetraminosForPositions(aPositions);
		vector<GamePositionOnBoard>::iterator tetraminosIterator;
		for (tetraminosIterator = aPositions.begin(); tetraminosIterator != aPositions.end(); tetraminosIterator++)
		{
			GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
			_delegate->removeTetraminoOnPositionXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		}
	}
}

void DamageToPlayerSpell::removeTetramninos(std::vector<GamePositionOnBoard> aPositions)
{
	vector<GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aPositions.begin(); tetraminosIterator != aPositions.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		_gameBoard->removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
}

void DamageToPlayerSpell::setDelegate(ExplosionAnimationDelegate *aDelegate)
{
	_delegate = aDelegate;
}