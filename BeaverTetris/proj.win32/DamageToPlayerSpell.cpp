#include "DamageToPlayerSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "TetraminosSeparatorDelegate.h"
#include "ActiveDetails.h"
#include "GameEnums.h"

using namespace std;

DamageToPlayerSpell::DamageToPlayerSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}


DamageToPlayerSpell::~DamageToPlayerSpell(void)
{
}

bool DamageToPlayerSpell::spellAvailable(void)
{
	bool spellAvailable = true;

	vector<int> linesWithUnpeacefulCount = getLinesWithUnpeacefulCount();

	if (linesWithUnpeacefulCount.size <= 0)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void DamageToPlayerSpell::castSpell()
{
	vector<int> linesWithUnpeacefulCount = getLinesWithUnpeacefulCount();

	vector<int>::iterator linesIterator;

	for (linesIterator = linesWithUnpeacefulCount.begin; linesIterator != linesWithUnpeacefulCount.end; linesIterator++)
	{
		makeReductionInLine(*linesIterator);
	}

	if (_someTetraminosWasRemoved)
	{
		separateTetraminos();
		_someTetraminosWasRemoved = false;
	}

}

vector<int> DamageToPlayerSpell::getLinesWithUnpeacefulCount()
{
	vector<int> linesWithUnpeacefulCount;

	for (int heightIndex = 0; heightIndex < _gameBoard->getGameBoardHeight; heightIndex++)
	{
		vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos = getUnEmptyAndNoBossesTetraminosInLine(heightIndex);

		if (unEmptyAndNoBossesTetraminos.size > minPeacefulNonEmptyTetraminosCount)
		{
			linesWithUnpeacefulCount.push_back(heightIndex);
		}

	}
	return linesWithUnpeacefulCount;
}

vector<GamePositionOnBoard> DamageToPlayerSpell::getUnEmptyAndNoBossesTetraminosInLine(int aLine)
{

	vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos;

	for (int widthIndex = 0; widthIndex < _gameBoard->getGameBoardWidth; widthIndex++)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aLine);
		if (tetraminoInBoard->getTetraminoType > kTetraminoEmpty && tetraminoInBoard->getTetraminoType < kTetraminoBossQueen)
		{
			GamePositionOnBoard tetraminoInBoardPosition;
			tetraminoInBoardPosition.xPosition = widthIndex;
			tetraminoInBoardPosition.yPosition = aLine;
			unEmptyAndNoBossesTetraminos.push_back(tetraminoInBoardPosition);

		}

	}
	return unEmptyAndNoBossesTetraminos;
}

void DamageToPlayerSpell::makeReductionInLine(int aLine)
{
	vector<GamePositionOnBoard> unEmptyAndNoBossesTetraminos = getUnEmptyAndNoBossesTetraminosInLine(aLine);
	int reductionCount = unEmptyAndNoBossesTetraminos.size - minPeacefulNonEmptyTetraminosCount;

	for (int reductionIndex = 0; reductionIndex <= reductionCount; reductionIndex++)
	{
		int reductionElementIndex = GameHelper::getRandomNumberFromUpInterval(unEmptyAndNoBossesTetraminos.size);
		GamePositionOnBoard tetraminoPosition = unEmptyAndNoBossesTetraminos[reductionElementIndex];
		_gameBoard->removeTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		unEmptyAndNoBossesTetraminos.erase(unEmptyAndNoBossesTetraminos.begin + reductionElementIndex);
		_someTetraminosWasRemoved = true;
	}

}


void DamageToPlayerSpell::separateTetraminos()
{
	ActiveDetails *activeDetails = (ActiveDetails*)ServiceLocator::getServiceForKey(activeDetailsKey);
	TetraminosSeparatorDelegate *separatorDelegate = new TetraminosSeparatorDelegate(_gameBoard, activeDetails);
	separatorDelegate->separateTetraminos;
}