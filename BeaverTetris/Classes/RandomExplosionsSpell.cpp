#include "RandomExplosionsSpell.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameHelper.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "ExplosionAnimationDelegate.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

RandomExplosionsSpell::RandomExplosionsSpell(void)
{
	_gameBoard = (GameBoard*)ServiceLocator::getServiceForKey(gameBoardKey);
	_delegate = NULL;
	CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_randomExplosionsCount = currentPlayerDataSource->getSpellCountForKey(removeRandomTetraminosSpellKey);
}


RandomExplosionsSpell::~RandomExplosionsSpell(void)
{
}

bool RandomExplosionsSpell::spellAvailable(void)
{
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	bool spellAvailable = true;
	if (availableTetraminos.size() < _randomExplosionsCount)
	{
		spellAvailable = false;
	}
	return spellAvailable;
}

void RandomExplosionsSpell::castSpell()
{
	srand(time(0));
	vector <GamePositionOnBoard> explosionTetraminos = getTetraminosForExplosion();
	reduceLivesInTetraminos(explosionTetraminos);
	sendMessageToDelegateWithTetraminos(explosionTetraminos);
	removeKilledTetraminos(explosionTetraminos);
}

vector <GamePositionOnBoard> RandomExplosionsSpell::getTetraminosForExplosion()
{
	vector <GamePositionOnBoard> tetraminosForExplosion;
	vector <GamePositionOnBoard> availableTetraminos = _gameBoard->getAvailableTetraminis();
	for (int removeTetraminoIndex = 0; removeTetraminoIndex < _randomExplosionsCount; removeTetraminoIndex++)
	{
		int randomTetramino = GameHelper::getRandomNumberFromUpInterval(availableTetraminos.size());
		GamePositionOnBoard tetraminoPosition = availableTetraminos[randomTetramino];
		availableTetraminos.erase(availableTetraminos.begin() + randomTetramino);
		tetraminosForExplosion.push_back(tetraminoPosition);
	}
	return tetraminosForExplosion;
}

void RandomExplosionsSpell::reduceLivesInTetraminos(vector <GamePositionOnBoard> aTetraminos)
{
	vector <GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetramino = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		tetramino->reduceLive();
	}
}

void RandomExplosionsSpell::sendMessageToDelegateWithTetraminos(std::vector <GamePositionOnBoard> aTetraminos)
{
	if (_delegate)
	{
		_delegate->blowUpTetraminosForPositions(aTetraminos);
		sendDelegateKilledTetraminos(aTetraminos);
	}
}

void RandomExplosionsSpell::sendDelegateKilledTetraminos(std::vector <GamePositionOnBoard> aTetraminos)
{
	vector <GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetramino = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		if (tetramino->getTetraminoLivesCount() <= 0)
		{
			_delegate->removeTetraminoOnPositionXY(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		}
	}
}

void RandomExplosionsSpell::removeKilledTetraminos(std::vector <GamePositionOnBoard> aTetraminos)
{
	vector <GamePositionOnBoard>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		GamePositionOnBoard tetraminoPosition = *tetraminosIterator;
		Tetramino *tetramino = _gameBoard->getTetraminoForXYposition(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
		_gameBoard->removeTetraminoForXYpositionIfItHasNoLives(tetraminoPosition.xPosition, tetraminoPosition.yPosition);
	}
}

void RandomExplosionsSpell::setDelegate(ExplosionAnimationDelegate *aDelegate)
{
	_delegate = aDelegate;
}
