#include "FirestromSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "FirestormSpellDelegate.h"

using namespace std;

FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
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
	vector <  vector<GamePositionOnBoard> > explosionsZones = getExplosionsZones();
	reduceLivesInExplosionsZones(explosionsZones);
	sendMassegeToDelegateWithExplosionsZones(explosionsZones);
	removeKilledTetraminosFromExplosionsZones(explosionsZones);
}

vector <  vector<GamePositionOnBoard> > FirestromSpell::getExplosionsZones()
{
	vector <  vector<GamePositionOnBoard> > explosionsZones;
	for (int meteorIndex = 0; meteorIndex <= meteorsCount; meteorIndex++)
	{
		int randomMeteorPositionX = GameHelper::getRandomNumberFromUpInterval(_gameBoard->getGameBoardWidth());
		vector<GamePositionOnBoard> explosionsZone = getExplosionsZonesWithXPosition(randomMeteorPositionX);
		explosionsZones.push_back(explosionsZone);
	}
	return explosionsZones;
}

vector<GamePositionOnBoard> FirestromSpell::getExplosionsZonesWithXPosition(int xPosition)
{
	GamePositionOnBoard explosionPosition = getExplosionPositionFromMeteorX(xPosition);
	vector<GamePositionOnBoard> explosionZone = getExplosionZoneOnPosition(explosionPosition);
	return explosionZone;
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

void FirestromSpell::reduceLivesInExplosionsZones(vector <  vector<GamePositionOnBoard> > aExplosionsZones)
{
	OperationWithPosition reduceTetraminoLivesOperation = [this](GamePositionOnBoard aPosition){
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		tetraminoInBoard->reduceLive();
	};
	makeOperationWithZonesPositions(aExplosionsZones, reduceTetraminoLivesOperation);
}

void FirestromSpell::sendMassegeToDelegateWithExplosionsZones(vector <  vector<GamePositionOnBoard> > aExplosionsZones)
{
	if (_delegate)
	{
		sendDelegateExplosionPositions(aExplosionsZones);
		sendDelegateKilledTetraminos(aExplosionsZones);
	}
}

void FirestromSpell::sendDelegateExplosionPositions(vector <  vector<GamePositionOnBoard> > aExplosionsZones)
{
	vector <  vector<GamePositionOnBoard> >::iterator zonesIterator;
	for (zonesIterator = aExplosionsZones.begin(); zonesIterator != aExplosionsZones.end(); zonesIterator++)
	{
		vector<GamePositionOnBoard> zone = *zonesIterator;
		_delegate->blowUpTetraminosForPositions(zone);
	}
}

void FirestromSpell::sendDelegateKilledTetraminos(vector <  vector<GamePositionOnBoard> > aExplosionsZones)
{
	OperationWithPosition sendDelegateKilledTetraminoOperation = [this](GamePositionOnBoard aPosition){
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		if (tetraminoInBoard->getTetraminoLivesCount() <= 0 && tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			_delegate->removeTetraminoOnPositionXY(aPosition.xPosition, aPosition.yPosition);
		}
	};
	makeOperationWithZonesPositions(aExplosionsZones, sendDelegateKilledTetraminoOperation);
}

void FirestromSpell::removeKilledTetraminosFromExplosionsZones(vector <  vector<GamePositionOnBoard> > aExplosionsZones)
{
	OperationWithPosition removeKilledTetraminosOperation = [this](GamePositionOnBoard aPosition){
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(aPosition.xPosition, aPosition.yPosition);
	};
	makeOperationWithZonesPositions(aExplosionsZones, removeKilledTetraminosOperation);
}

void FirestromSpell::makeOperationWithZonesPositions(vector <  vector<GamePositionOnBoard> > &aZones, OperationWithPosition aOperation)
{
	vector <  vector<GamePositionOnBoard> >::iterator zonesIterator;
	for (zonesIterator = aZones.begin(); zonesIterator != aZones.end(); zonesIterator++)
	{
		vector<GamePositionOnBoard> zone = *zonesIterator;
		makeOperationWithZonePositions(zone, aOperation);
	}
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