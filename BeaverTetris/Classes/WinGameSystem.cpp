#include "WinGameSystem.h"
#include "GameBoard.h"
#include "Tetramino.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"

using namespace std;

WinGameSystem::WinGameSystem(GameBoard *aGameBoard)
{
	_gameBoard = aGameBoard;
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
}


WinGameSystem::~WinGameSystem(void)
{
}


void WinGameSystem::updateSystem(float deltaTime)
{
	if (loseGameChecker())
	{
		_gameTimeStepController->setUpdateAvailable(false);
		cocos2d::log("Lose game");
	}
}

bool WinGameSystem::loseGameChecker()
{
	bool isThereTetraminoInLoseZone = false;
	int loseHeight = _gameBoard->getGameBoardHeight() - 1;
	
	for (int xIndex = 0; xIndex < _gameBoard->getGameBoardWidth(); xIndex++)
	{
		Tetramino *tetraminoIngameBoard = _gameBoard->getTetraminoForXYposition(xIndex, loseHeight);
		if (tetraminoIngameBoard->getTetraminoType() > kTetraminoEmpty)
		{
			isThereTetraminoInLoseZone = true;
			break;
		}
	}
	return isThereTetraminoInLoseZone;
}