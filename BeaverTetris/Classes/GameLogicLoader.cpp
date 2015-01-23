#include "GameLogicLoader.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameDesignConstants.h"

#include "GameBoard.h"

GameLogicLoader::GameLogicLoader(void)
{
}


GameLogicLoader::~GameLogicLoader(void)
{
}

void GameLogicLoader::loadResources()
{
	GameBoard *gameBoard = new GameBoard(tetrisBlocksWidth, tetrisBlocksHeight);
	ServiceLocator::setServiceForKey(gameBoard, gameBoardKey);

}