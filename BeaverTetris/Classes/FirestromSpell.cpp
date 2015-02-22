#include "FirestromSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"

using namespace std;

FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}

FirestromSpell::~FirestromSpell(void)
{
}

bool FirestromSpell::spellAvailable(void)
{
	bool spellAvailable = true;
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	if (availableTetraminos.size() <= 0)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void FirestromSpell::castSpell()
{
	for (int meteorIndex = 0; meteorIndex <= meteorsCount; meteorIndex++)
	{
		int randomMeteorPositionX = GameHelper::getRandomNumberFromUpInterval(_gameBoard->getGameBoardWidth());
		runFireballWithXPosition(randomMeteorPositionX);
	}
}

void FirestromSpell::runFireballWithXPosition(int positionX)
{
	int explosionHeight = 0;
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	for (int heightIndex = (gameBoardHeight - 1); heightIndex > 0; heightIndex--)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(positionX, heightIndex);
		if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			explosionHeight = heightIndex + 1;
			break;
		}
	}
	makeExplosionOnPositionXY(positionX, explosionHeight);
}

void FirestromSpell::makeExplosionOnPositionXY(int positionX, int positionY)
{
	int upHeight = positionY + meteorAreaExplosionLength;
	int downHeight = positionY - meteorAreaExplosionLength;
	for (int heightIndex = downHeight; heightIndex <= upHeight; heightIndex++)
	{
		makeExplosionInRowAndExplosionX(heightIndex, positionX);
	}
}

void FirestromSpell::makeExplosionInRowAndExplosionX(int aRow, int explosionX)
{
	int upWidth = explosionX + meteorAreaExplosionLength;
	int downWidth = explosionX - meteorAreaExplosionLength;
	for (int widthIndex = downWidth; widthIndex <= upWidth; widthIndex++)
	{
		GamePositionOnBoard explosionPosition;
		explosionPosition.xPosition = widthIndex;
		explosionPosition.yPosition = aRow;
		if (_gameBoard->positionInBoard(explosionPosition))
		{
			Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, aRow);
			tetraminoInBoard->reduceLive();
			_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(widthIndex, aRow);
		}
	}
}