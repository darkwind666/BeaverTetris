#include "GameWorldAnimationController.h"
#include "AnimationSynchonizer.h"
#include "CurrentDetailAnimationControler.h"
#include "FullLineCombinationAnimationController.h"
#include "SimilarTetraminosAnimationController.h"
#include "FillingGapInBoardAnimationController.h"
#include "DamageToPlayerSpellAnimationController.h"

GameWorldAnimationController::GameWorldAnimationController(GameBoardController *aGameBoardController)
{
	_gameBoardController = aGameBoardController;
	_animationSynchonizer = new AnimationSynchonizer();
	makeAnimationControllers();
}


GameWorldAnimationController::~GameWorldAnimationController(void)
{
}

void GameWorldAnimationController::makeAnimationControllers()
{
	this->addChild(_animationSynchonizer);

	CurrentDetailAnimationControler *currentDetailAnimationControler = new CurrentDetailAnimationControler(_gameBoardController, _animationSynchonizer);
	this->addChild(currentDetailAnimationControler);

	FullLineCombinationAnimationController *fullLineCombinationAnimationController = new FullLineCombinationAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(fullLineCombinationAnimationController);

	SimilarTetraminosAnimationController *similarTetraminosAnimationController = new SimilarTetraminosAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(similarTetraminosAnimationController);

	FillingGapInBoardAnimationController *fillingGapInBoardAnimationController = new FillingGapInBoardAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(fillingGapInBoardAnimationController);

	DamageToPlayerSpellAnimationController *damageToPlayerSpellAnimationController = new DamageToPlayerSpellAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(damageToPlayerSpellAnimationController);

}

void GameWorldAnimationController::updateAnimation()
{
	_animationSynchonizer->updateSynchonizer();
}