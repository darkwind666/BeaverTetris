#include "ExplosionsForTutorialController.h"
#include "TetraminoExplosionFactory.h"
#include "GameAnimationActionsConstants.h"
#include "GameDesignConstants.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;
using namespace std;

ExplosionsForTutorialController::ExplosionsForTutorialController(void)
{
}


ExplosionsForTutorialController::~ExplosionsForTutorialController(void)
{
}

FiniteTimeAction* ExplosionsForTutorialController::getTetraminosExplosionAnimationForCallback(function<void()> aCallback)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create(aCallback);
	FiniteTimeAction *delay = DelayTime::create(tetraminosExplosionDuration);
	FiniteTimeAction *sequence = Sequence::create(tetraminosLineExplosionAnimation, delay, NULL);
	FiniteTimeAction *blowUpAnimation = TargetedAction::create(this, sequence);
	return blowUpAnimation;
}

void ExplosionsForTutorialController::makeBottomExplosionWithHeight(int aHeight)
{
	for (int explosionIndex = 0; explosionIndex < tetrisBlocksWidth; explosionIndex++)
	{
		setExplosionForIndexXY(explosionIndex, aHeight);
	}
}

void ExplosionsForTutorialController::getHorizontalLineCombinationExplosion()
{
	for (int explosionIndex = 2; explosionIndex < 6; explosionIndex++)
	{
		setExplosionForIndexXY(explosionIndex, 1);
	}
}

void ExplosionsForTutorialController::getVericalLineCombinationExplosion()
{
	for (int explosionIndex = 0; explosionIndex < 5; explosionIndex++)
	{
		setExplosionForIndexXY(2, explosionIndex);
	}
}

void ExplosionsForTutorialController::getSpellExplosion()
{
	for (int explosionIndex = 16; explosionIndex < 19; explosionIndex++)
	{
		setExplosionForIndexXY(2, explosionIndex);
	}
	setExplosionForIndexXY(3, 18);
}

void ExplosionsForTutorialController::makeRandomSpellExplosions()
{
	setExplosionForIndexXY(1, 1);
	setExplosionForIndexXY(3, 1);
	setExplosionForIndexXY(2, 1);
	setExplosionForIndexXY(2, 2);
	setExplosionForIndexXY(3, 2);
	setExplosionForIndexXY(6, 3);
	setExplosionForIndexXY(5, 3);
	setExplosionForIndexXY(8, 3);
}

void ExplosionsForTutorialController::makeFirestormSpellExplosions()
{
	setExplosionAroundX(2);
	setExplosionAroundX(4);
	setExplosionAroundX(6);
	setExplosionAroundX(8);
}

void ExplosionsForTutorialController::setExplosionAroundX(int xIndex)
{
	setExplosionForIndexXY(xIndex - 1, 4);
	setExplosionForIndexXY(xIndex, 4);
	setExplosionForIndexXY(xIndex + 1, 4);
	setExplosionForIndexXY(xIndex - 1, 3);
	setExplosionForIndexXY(xIndex, 3);
	setExplosionForIndexXY(xIndex + 1, 3);
	setExplosionForIndexXY(xIndex - 1, 2);
	setExplosionForIndexXY(xIndex, 2);
	setExplosionForIndexXY(xIndex + 1, 2);
}

void ExplosionsForTutorialController::makeCohesionSpellExplosions()
{
	makeBottomExplosionWithHeight(1);
	makeBottomExplosionWithHeight(2);
}

void ExplosionsForTutorialController::setExplosionForIndexXY(int xIndex, int yIndex)
{
	ParticleSystem *explosion = getExplosion();
	Vec2 explosionPosition = getTetraminoPositionForIndexXY(xIndex, yIndex);
	explosion->setPosition(explosionPosition);
	this->addChild(explosion);
}

ParticleSystem* ExplosionsForTutorialController::getExplosion()
{
	ParticleSystem *explosion = ParticleExplosion::create();
	explosion->setAutoRemoveOnFinish(true);
	TetraminoExplosionFactory::setExplosionColors(explosion);
	TetraminoExplosionFactory::setExplosionParticles(explosion);
	return explosion;
}

Vec2 ExplosionsForTutorialController::getTetraminoPositionForIndexXY(int xIndex, int yIndex)
{
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 position = Vec2(offset.x * xIndex, offset.y * yIndex);
	return position;
}

FiniteTimeAction* ExplosionsForTutorialController::getFirestormAnimation()
{
	FiniteTimeAction *meteor1Animation = getMeteorAnimationForIndex(2);
	FiniteTimeAction *meteor2Animation = getMeteorAnimationForIndex(4);
	FiniteTimeAction *meteor3Animation = getMeteorAnimationForIndex(6);
	FiniteTimeAction *meteor4Animation = getMeteorAnimationForIndex(8);

	FiniteTimeAction *spawn = Spawn::create(meteor1Animation, meteor2Animation, meteor3Animation, meteor4Animation, nullptr);
	FiniteTimeAction *animationWithMeteors = TargetedAction::create(this, spawn);
	return animationWithMeteors;

}

FiniteTimeAction* ExplosionsForTutorialController::getMeteorAnimationForIndex(int aIndex)
{
	ParticleSystem *meteor = ParticleMeteor::create();
	meteor->setGravity(Vec2(0,400));
	Vec2 meteorPosition = getTetraminoPositionForIndexXY(aIndex, 23);
	meteor->setPosition(meteorPosition);
	this->addChild(meteor);

	Vec2 meteorFinalPosition = getTetraminoPositionForIndexXY(aIndex, 3);
	FiniteTimeAction *moveMeteor = MoveTo::create(0.3f, meteorFinalPosition);
	FiniteTimeAction *setStartRocketPosition = Place::create(meteor->getPosition());
	FiniteTimeAction *meteorSequence = Sequence::create(moveMeteor, setStartRocketPosition, nullptr);
	FiniteTimeAction *animationWithMeteor = TargetedAction::create(meteor, meteorSequence);
	return animationWithMeteor;
}