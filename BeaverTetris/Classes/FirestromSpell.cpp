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
	_removeCurrentDetail = false;
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
	_explosionPositionDelegate->cleanFirestorm();
	_removeCurrentDetail = false;
	vector<FireballInformation> fireballs = getFireballs();
	removeCurrentDetail();
	throwFireballs(fireballs);
}

vector<FireballInformation> FirestromSpell::getFireballs()
{
	vector<FireballInformation> fireballs;
	srand(time(0));
	for (int meteorIndex = 0; meteorIndex < _meteorsCount; meteorIndex++)
	{
		GamePositionOnBoard explosionPosition = getExplosionPosition();
		if (_explosionPositionDelegate->explosionInCurrentDetailWithPosition(explosionPosition) && _removeCurrentDetail == false)
		{
			_removeCurrentDetail = true;
			_explosionPositionInCurrentDetail = explosionPosition;
		}
		else
		{
			FireballInformation fireball = getFireballFromPosition(explosionPosition);
			fireballs.push_back(fireball);
		}
	}
	return fireballs;
}

GamePositionOnBoard FirestromSpell::getExplosionPosition()
{
	int randomMeteorPositionX = GameHelper::getRandomNumberFromUpInterval(_gameBoard->getGameBoardWidth());
	GamePositionOnBoard explosionPosition = _explosionPositionDelegate->getExplosionPositionFromMeteorX(randomMeteorPositionX);
	return explosionPosition;
}

FireballInformation  FirestromSpell::getFireballFromPosition(GamePositionOnBoard aExplosionPosition)
{
	FireballInformation fireball;
	fireball.explosionPosition = aExplosionPosition;
	fireball.explosionsZone = _explosionPositionDelegate->getExplosionZoneOnPosition(aExplosionPosition);
	return fireball;
}

void FirestromSpell::removeCurrentDetail()
{
	if (_removeCurrentDetail)
	{
		sendMassegeToDelegateToDeleteCurrentDetailWithPosition(_explosionPositionInCurrentDetail);
		_currentDetailDataSource->removeCurrentDetail();
	}
}

void FirestromSpell::throwFireballs(vector<FireballInformation> aFireballs)
{
	sendMassegeToDelegateWithFireballs(aFireballs);
	removeKilledTetraminosFromFireballs(aFireballs);
}

void FirestromSpell::sendMassegeToDelegateWithFireballs(vector<FireballInformation> aFireballs)
{
	if (_delegate)
	{
		vector<FireballInformation>::iterator fireballsIterator;
		for (fireballsIterator = aFireballs.begin(); fireballsIterator != aFireballs.end(); fireballsIterator++)
		{
			FireballInformation fireball = *fireballsIterator;
			vector<GamePositionOnBoard> explosionZone = fireball.explosionsZone;
			_delegate->blowUpTetraminosAreaOnPosition(fireball.explosionsZone, fireball.explosionPosition);
		}
		//_delegate->throwFireballs(aFireballs);
	}
}

void FirestromSpell::removeKilledTetraminosFromFireballs(vector<FireballInformation> aFireballs)
{
	vector<FireballInformation>::iterator fireballsIterator;
	for (fireballsIterator = aFireballs.begin(); fireballsIterator != aFireballs.end(); fireballsIterator++)
	{
		FireballInformation fireball = *fireballsIterator;
		vector<GamePositionOnBoard> explosionZone = fireball.explosionsZone;
		removeKilledTetraminosFromExplosionZone(explosionZone);
	}
}

void FirestromSpell::removeKilledTetraminosFromExplosionZone(vector<GamePositionOnBoard> aExplosionsZone)
{
	vector<GamePositionOnBoard>::iterator positionsIterator;
	for (positionsIterator = aExplosionsZone.begin(); positionsIterator != aExplosionsZone.end(); positionsIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *positionsIterator;
		reduceLiveOnPosition(tetraminoPosition);
		sendDelegateKilledTetraminoOnPosition(tetraminoPosition);
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
}

void FirestromSpell::reduceLiveOnPosition(GamePositionOnBoard aPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
	tetraminoInBoard->reduceLive();
}

void FirestromSpell::sendDelegateKilledTetraminoOnPosition(GamePositionOnBoard aPosition)
{
	if (_delegate)
	{
		Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(aPosition.xPosition, aPosition.yPosition);
		if (tetraminoInBoard->getTetraminoLivesCount() <= 0 && tetraminoInBoard->getTetraminoType() > kTetraminoEmpty)
		{
			_delegate->removeTetraminoOnPositionXY(aPosition.xPosition, aPosition.yPosition);
		}
	}
}

void FirestromSpell::setDelegate(FirestormSpellDelegate *aDelegate)
{
	_delegate = aDelegate;
}