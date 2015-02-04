#include "GameWorldAnimationController.h"
#include "CurrentDetailAnimationControler.h"
#include "FullLineCombinationAnimationController.h"

GameWorldAnimationController::GameWorldAnimationController(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	makeAnimationControllers();
}


GameWorldAnimationController::~GameWorldAnimationController(void)
{
}

void GameWorldAnimationController::makeAnimationControllers()
{
	CurrentDetailAnimationControler *currentDetailAnimationControler = new CurrentDetailAnimationControler(_gameBoardController);
	this->addChild(currentDetailAnimationControler);

	FullLineCombinationAnimationController *fullLineCombinationAnimationController = new FullLineCombinationAnimationController(_gameBoardController);
	this->addChild(fullLineCombinationAnimationController);
}