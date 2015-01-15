#include "GameBackgroundSoundRegulator.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;

GameBackgroundSoundRegulator::GameBackgroundSoundRegulator(void)
{
	CCSprite *sourceView = CCSprite::create("HelloWorld.png");
	sourceView->setScaleX(0.2f);
	sourceView->setScaleY(0.07f);
	sourceView->setColor(ccColor3B::BLUE);
	this->addChild(sourceView);
}


GameBackgroundSoundRegulator::~GameBackgroundSoundRegulator(void)
{
}
