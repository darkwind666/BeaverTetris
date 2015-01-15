#include "GameSoundEffectsRegulator.h"

using namespace cocos2d;

GameSoundEffectsRegulator::GameSoundEffectsRegulator(void)
{
	CCSprite *sourceView = CCSprite::create("HelloWorld.png");
	sourceView->setScaleX(0.2f);
	sourceView->setScaleY(0.07f);
	sourceView->setColor(ccColor3B::GRAY);
	this->addChild(sourceView);
}


GameSoundEffectsRegulator::~GameSoundEffectsRegulator(void)
{
}
