#include "FirestromSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "FirestormSpellDelegate.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewElementsKeys.h"
#include "CurrentDetailDataSource.h"
#include "FirestromSpellExplosionPositionDelegate.h"

using namespace std;

FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_meteorsCount = currentPlayerDataSource->getSpellCountForKey(firestormSpellKey);
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
	_explosionPositionDelegate = new FirestromSpellExplosionPositionDelegate();
}

FirestromSpell::~FirestromSpell(void)
{
	delete _explosionPositionDelegate;
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
		GamePositionOnBoard explosionPosition = _explosionPositionDelegate->getExplosionPositionFromMeteorX(randomMeteorPositionX);
		throwFireballOnPosition(explosionPosition);
	}
}

void FirestromSpell::throwFireballOnPosition(GamePositionOnBoard aExplosionPosition)
{
	if (_explosionPositionDelegate->explosionInCurrentDetailWithPosition(aExplosionPosition))
	{
		removeCurrentDetailWithPosition(aExplosionPosition);
	}
	else
	{
		vector<GamePositionOnBoard> explosionZone = _explosionPositionDelegate->getExplosionZoneOnPosition(aExplosionPosition);
		reduceLivesInExplosionsZone(explosionZone);
		sendMassegeToDelegateWithExplosionsZoneAndPosition(explosionZone, aExplosionPosition);
		removeKilledTetraminosFromExplosionsZone(explosionZone);
	}
}

void FirestromSpell::removeCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition)
{
	sendMassegeToDelegateToDeleteCurrentDetailWithPosition(aExplosionPosition);
	_currentDetailDataSource->removeCurrentDetail();
}

void FirestromSpell::sendMassegeToDelegateToDeleteCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition)
{
	if (_delegate)
	{
		_delegate->removeCurrentDetailWithExplosionPosition(aExplosionPosition);
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