#include "GameLogicLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

#include "GameBoard.h"

GameLogicLoader::GameLogicLoader(void)
{
}


GameLogicLoader::~GameLogicLoader(void)
{
}

void GameLogicLoader::loadResources()
{
	GameBoard *gameBoard = new GameBoard(20,20);
	ServiceLocator::setServiceForKey(gameBoard, gameBoardKey);

}