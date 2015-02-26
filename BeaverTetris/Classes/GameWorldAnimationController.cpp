#include "GameWorldAnimationController.h"
#include "AnimationSynchonizer.h"

#include "ExplosionAnimationController.h"
#include "RocketSpellAnimationController.h"
#include "FirestormSpellAnimationController.h"
#include "CohesionSpellAnimationController.h"
#include "FallenDetailAnimationController.h"

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

	ExplosionAnimationController *explosionAnimationController = new ExplosionAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(explosionAnimationController);

	RocketSpellAnimationController *rocketSpellAnimationController = new RocketSpellAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(rocketSpellAnimationController);

	FirestormSpellAnimationController *firestormSpellAnimationController = new FirestormSpellAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(firestormSpellAnimationController);

	CohesionSpellAnimationController *cohesionSpellAnimationController = new CohesionSpellAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(cohesionSpellAnimationController);

	FallenDetailAnimationController *fallenDetailAnimationController = new FallenDetailAnimationController(_gameBoardController, _animationSynchonizer);
	this->addChild(fallenDetailAnimationController);
}

void GameWorldAnimationController::updateAnimation()
{
	_animationSynchonizer->updateSynchonizer();
}