#pragma once

#include "cocos2d.h"
#include <functional>

class ExplosionsForTutorialController : public cocos2d::Node
{
public:
	ExplosionsForTutorialController(void);
	~ExplosionsForTutorialController(void);

	void makeBottomExplosionWithHeight(int aHeight);
	void getHorizontalLineCombinationExplosion();
	void getVericalLineCombinationExplosion();
	void getSpellExplosion();
	void makeRandomSpellExplosions();
	cocos2d::FiniteTimeAction* getFirestormAnimation();
	void makeFirestormSpellExplosions();
	void makeCohesionSpellExplosions();
	cocos2d::FiniteTimeAction* getTetraminosExplosionAnimationForCallback(std::function<void()> aCallback);
	void setExplosionForIndexXY(int xIndex, int yIndex);
	cocos2d::ParticleSystem* getExplosion();

private:

	cocos2d::Vec2 getTetraminoPositionForIndexXY(int xIndex, int yIndex);
	cocos2d::FiniteTimeAction* getMeteorAnimationForIndex(int aIndex);
	void setExplosionAroundX(int xIndex);

};

