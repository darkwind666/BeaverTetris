#include "GameWorldAnimationController.h"
#include "AnimationSynchonizer.h"
#include "CurrentDetailAnimationControler.h"
#include "FillingGapInBoardAnimationController.h"
#include "ExplosionAnimationController.h"
#include "RocketSpellAnimationController.h"

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

	FillingGapInBoardAnimationController *fillingGapInBoardAnimationController = new FillingGapInBoardAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(fillingGapInBoardAnimationController);

	ExplosionAnimationController *explosionAnimationController = new ExplosionAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(explosionAnimationController);

	RocketSpellAnimationController *rocketSpellAnimationController = new RocketSpellAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(rocketSpellAnimationController);

}

void GameWorldAnimationController::updateAnimation()
{
	_animationSynchonizer->updateSynchonizer();
}