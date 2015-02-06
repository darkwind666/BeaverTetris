#include "GameWorldAnimationController.h"
#include "CurrentDetailAnimationControler.h"
#include "FullLineCombinationAnimationController.h"
#include "FillingGapInBoardAnimationController.h"

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

	FillingGapInBoardAnimationController *fillingGapInBoardAnimationController = new FillingGapInBoardAnimationController(_gameBoardController);
	this->addChild(fillingGapInBoardAnimationController);
}