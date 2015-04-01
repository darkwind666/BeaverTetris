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
#include "CurrentDetailDataSource.h"
#include "TetraminoDetail.h"

using namespace std;

FirestromSpell::FirestromSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_meteorsCount = currentPlayerDataSource->getSpellCountForKey(firestormSpellKey);
	_currentDetailDataSource = (CurrentDetailDataSource*)ServiceLocator::getServiceForKey(currentDetailDataSourceKey);
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
		throwFireballOnPosition(explosionPosition);
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
		if (checkExplosionInCurrentDetailWithXYPosition(xPosition, heightIndex))
		{
			explosionHeight = heightIndex + 1;
			break;
		}
		else
		{
			if (checkExplosionInBoardWithXYPosition(xPosition, heightIndex))
			{
				explosionHeight = heightIndex + 1;
				break;
			}
		}

	}
	return explosionHeight;
}

bool FirestromSpell::checkExplosionInCurrentDetailWithXYPosition(int xPosition, int yPosition)
{
	bool inCurrentDetail = false;
	if (_currentDetailDataSource->currentDetailAvailable())
	{
		GamePositionOnBoard absolutePosition;
		absolutePosition.xPosition = xPosition;
		absolutePosition.yPosition = yPosition;
		inCurrentDetail = checkExplosionInCurrentDetailWithAbsolutePosition(absolutePosition);
	}
	return inCurrentDetail;
}

bool FirestromSpell::checkExplosionInCurrentDetailWithAbsolutePosition(GamePositionOnBoard aPosition)
{
	bool inCurrentDetail = false;
	TetraminoDetail *currentDetail = _currentDetailDataSource->getCurrentDetail();
	if (currentDetail->absolutePositionInDetail(aPosition))
	{
		GamePositionOnBoard positionInDetail = currentDetail->convertAbsolutePositionToPositionInDetail(aPosition);
		Tetramino *tetraminoInCurrentDetail = currentDetail->getTetraminoForXY(positionInDetail.xPosition, positionInDetail.yPosition);
		if (tetraminoInCurrentDetail->getTetraminoType() > kTetraminoEmpty)
		{
			inCurrentDetail = true;
		}
	}
	return inCurrentDetail;
}

bool FirestromSpell::checkExplosionInBoardWithXYPosition(int xPosition, int yPosition)
{
	Tetramino *tetraminoInBoard = _gameBoard->getTetraminoForXYposition(xPosition, yPosition);
	bool inBoard = (tetraminoInBoard->getTetraminoType() > kTetraminoEmpty);
	return inBoard;
}

void FirestromSpell::throwFireballOnPosition(GamePositionOnBoard aExplosionPosition)
{
	if (explosionInCurrentDetailWithPosition(aExplosionPosition))
	{
		removeCurrentDetailWithPosition(aExplosionPosition);
	}
	else
	{
		vector<GamePositionOnBoard> explosionZone = getExplosionZoneOnPosition(aExplosionPosition);
		reduceLivesInExplosionsZone(explosionZone);
		sendMassegeToDelegateWithExplosionsZoneAndPosition(explosionZone, aExplosionPosition);
		removeKilledTetraminosFromExplosionsZone(explosionZone);
	}
}

bool FirestromSpell::explosionInCurrentDetailWithPosition(GamePositionOnBoard aExplosionPosition)
{
	GamePositionOnBoard realExplosionPosition = aExplosionPosition;
	realExplosionPosition.yPosition = realExplosionPosition.yPosition - 1;
	bool inCurrentDetail = checkExplosionInCurrentDetailWithXYPosition(realExplosionPosition.xPosition, realExplosionPosition.yPosition);
	return inCurrentDetail;
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