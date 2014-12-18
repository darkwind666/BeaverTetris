#include "RandomExplosionsSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "ActiveDetails.h"

using namespace std;

RandomExplosionsSpell::RandomExplosionsSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_someTetraminosWasRemoved = false;
}


RandomExplosionsSpell::~RandomExplosionsSpell(void)
{
}

bool RandomExplosionsSpell::spellAvailable(void)
{
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	bool spellAvailable = true;

	if (availableTetraminos.size() < randomExplosionsCount)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void RandomExplosionsSpell::castSpell()
{
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();

	for (int removeTetraminoIndex = 0; removeTetraminoIndex <= randomExplosionsCount; removeTetraminoIndex++)
	{
		removeRandomTetraminoInAvailableTetraminos(availableTetraminos);
	}
}

void RandomExplosionsSpell::removeRandomTetraminoInAvailableTetraminos(std::vector <GamePositionOnBoard> &availableTetraminos)
{
	int randomTetramino = GameHelper::getRandomNumberFromUpInterval(availableTetraminos.size());
	GamePositionOnBoard tetraminoPosition = availableTetraminos[randomTetramino];
	Tetramino *tetramino = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	
	tetramino->reduceLive();
	
	availableTetraminos.erase(availableTetraminos.begin() + randomTetramino);
}
