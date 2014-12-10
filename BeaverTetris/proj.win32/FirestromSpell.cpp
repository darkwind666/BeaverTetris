#include "FirestromSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "TetraminosSeparatorDelegate.h"
#include "ActiveDetails.h"


FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
}

FirestromSpell::~FirestromSpell(void)
{
}

bool FirestromSpell::spellAvailable(void)
{
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis;

	bool spellAvailable = true;

	if (availableTetraminos.size <= 0)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void FirestromSpell::castSpell()
{

	for (int meteorIndex = 0; meteorIndex <= meteorsCount; meteorIndex++)
	{
		int randomMeteorPositionX = GameHelper::getRandomNumberFromUpInterval(_gameBoard->getGameBoardWidth);
		runFireballWithXPosition(randomMeteorPositionX);
	}

	removeDeathTetraminos();
}

void FirestromSpell::runFireballWithXPosition(int positionX)
{
	bool wasExplosion = false;
	
	for (int heightIndex = _gameBoard->getGameBoardHeight; heightIndex < 0; heightIndex--)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(positionX, heightIndex);
	
		if (tetraminoInBoard->getTetraminoType > kTetraminoEmpty)
		{
			makeExplosionOnPositionXY(positionX, heightIndex);
			wasExplosion = true;
			break;
		}
	
	}
	
	if (!wasExplosion)
	{
		makeExplosionOnPositionXY(positionX, 0);
	}
}

void FirestromSpell::makeExplosionOnPositionXY(int positionX, int positionY)
{
	int upWidth = positionX + meteorAreaExplosionLength;
	int downWidth = positionX - meteorAreaExplosionLength;
	int upHeight = positionY + meteorAreaExplosionLength;
	int downHeight = positionY - meteorAreaExplosionLength;

	for (int heightIndex = downHeight; heightIndex <= upHeight; heightIndex++)
	{

		bool availableHeight = (heightIndex >= 0 && heightIndex <= _gameBoard->getGameBoardHeight);

		for (int widthIndex = downWidth; widthIndex <= upWidth; widthIndex++)
		{

			bool availableWidth = (widthIndex >= 0 && widthIndex <= _gameBoard->getGameBoardWidth);

			if (availableHeight && availableWidth)
			{
				Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(widthIndex, heightIndex);
				tetraminoInBoard->reduceLive;

				if (tetraminoInBoard->getTetraminoLivesCount <= 0)
				{
					_gameBoard->removeTetraminoForXYposition(widthIndex, heightIndex);
					_someTetraminosWasRemoved = true;
				}

			}

		}

	}

}

void FirestromSpell::removeDeathTetraminos()
{
	if (_someTetraminosWasRemoved)
	{
		ActiveDetails *activeDetails = (ActiveDetails*)ServiceLocator::getServiceForKey(activeDetailsKey);
		TetraminosSeparatorDelegate *separatorDelegate = new TetraminosSeparatorDelegate(_gameBoard, activeDetails);
		separatorDelegate->separateTetraminos;
		_someTetraminosWasRemoved = false;
	}
}