#include "FirestromSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "FirestormSpellDelegate.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_meteorsCount = currentPlayerDataSource->getSpellCountForKey(firestormSpellKey);
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
	srand(time(0));
	for (int meteorIndex = 0; meteorIndex < _meteorsCount; meteorIndex++)
	{
		int randomMeteorPositionX = GameHelper::getRandomNumberFromUpInterval(_gameBoard->getGameBoardWidth());
		GamePositionOnBoard explosionPosition = getExplosionPositionFromMeteorX(randomMeteorPositionX);
		vector<GamePositionOnBoard> explosionZone = getExplosionZoneOnPosition(explosionPosition);
		reduceLivesInExplosionsZone(explosionZone);
		sendMassegeToDelegateWithExplosionsZoneAndPosition(explosionZone, explosionPosition);
		removeKilledTetraminosFromExplosionsZone(explosionZone);
	}
}

GamePositionOnBoard FirestromSpell::getExplosionPositionFromMeteorX(int xPosition)
{
	int explosionHeight = getExplosionHeightFromExplosionX(xPosition);
	GamePositionOnBoard explosionPosition;
	explosionPosition.xPosition = xPosition;
	explosionPosition.yPosition = explosionHeight;
	return explosionPosition;
}

int FirestromSpell::getExplosionHeightFromExplosionX(int xPosition)
{
	int explosionHeight = 0;
	int gameBoardHeight = _gameBoard->getGameBoardHeight();
	for (int heightIndex = (gameBoardHeight - 1); heightIndex > 0; heightIndex--)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, heightIndex);
		if (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			explosionHeight = heightIndex + 1;
			break;
		}
	}
	return explosionHeight;
}

vector<GamePositionOnBoard> FirestromSpell::getExplosionZoneOnPosition(GamePositionOnBoard aExplosionPosition)
{
	vector<GamePositionOnBoard> explosionZone;
	int upHeight = aExplosionPosition.yPosition + meteorAreaExplosionLength;
	int downHeight = aExplosionPosition.yPosition - meteorAreaExplosionLength;
	for (int heightIndex = downHeight; heightIndex <= upHeight; heightIndex++)
	{
		fillExplosionZoneRowWithPosition(explosionZone, heightIndex, aExplosionPosition);
	}
	return explosionZone;
}

void FirestromSpell::fillExplosionZoneRowWithPosition(vector<GamePositionOnBoard> &explosionZone, int row, GamePositionOnBoard aExplosionPosition)
{
	int upWidth = aExplosionPosition.xPosition + meteorAreaExplosionLength;
	int downWidth = aExplosionPosition.xPosition - meteorAreaExplosionLength;
	for (int widthIndex = downWidth; widthIndex <= upWidth; widthIndex++)
	{
		GamePositionOnBoard explosionPosition;
		explosionPosition.xPosition = widthIndex;
		explosionPosition.yPosition = row;
		if (_gameBoard->positionInBoard(explosionPosition))
		{
			explosionZone.push_back(explosionPosition);
		}
	}
}

void FirestromSpell::reduceLivesInExplosionsZone(vector<GamePositionOnBoard> aExplosionZone)
{
	OperationWithPosition reduceTetraminoLivesOperation = [this](GamePositionOnBoard aPosition){
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		tetraminoInBoard->reduceLive();
	};
	makeOperationWithZonePositions(aExplosionZone, reduceTetraminoLivesOperation);
}

void FirestromSpell::sendMassegeToDelegateWithExplosionsZoneAndPosition(vector<GamePositionOnBoard> aExplosionsZone, GamePositionOnBoard aExplosionPosition)
{
	if (_delegate)
	{
		_delegate->blowUpTetraminosAreaOnPosition(aExplosionsZone, aExplosionPosition);
		sendDelegateKilledTetraminos(aExplosionsZone);
	}
}

void FirestromSpell::sendDelegateKilledTetraminos(vector<GamePositionOnBoard> aExplosionsZone)
{
	OperationWithPosition sendDelegateKilledTetraminoOperation = [this](GamePositionOnBoard aPosition){
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		if (tetraminoInBoard->getTetraminoLivesCount() <= 0 && tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			_delegate->removeTetraminoOnPositionXY(aPosition.xPosition, aPosition.yPosition);
		}
	};
	makeOperationWithZonePositions(aExplosionsZone, sendDelegateKilledTetraminoOperation);
}

void FirestromSpell::removeKilledTetraminosFromExplosionsZone(vector<GamePositionOnBoard> aExplosionsZone)
{
	OperationWithPosition removeKilledTetraminosOperation = [this](GamePositionOnBoard aPosition){
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(aPosition.xPosition, aPosition.yPosition);
	};
	makeOperationWithZonePositions(aExplosionsZone, removeKilledTetraminosOperation);
}

void FirestromSpell::makeOperationWithZonePositions(vector<GamePositionOnBoard> &aPositions, OperationWithPosition aOperation)
{
	vector<GamePositionOnBoard>::iterator positionsIterator;
	for (positionsIterator = aPositions.begin(); positionsIterator != aPositions.end(); positionsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionsIterator;
		aOperation(tetraminoPosition);
	}
}

void FirestromSpell::setDelegate(FirestormSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}