#include "LoadGameController.h"

using namespace std;
using namespace cocos2d;

LoadGameController::LoadGameController(void)
{
	CCSprite *sourceView = CCSprite::create("HelloWorld.png");
	_loadGameControllerView =  CCProgressTimer::create(sourceView);
	_loadGameControllerView->setPercentage(0);
	_loadGameControllerView->setScale(0.2f);
	this->addChild(_loadGameControllerView);
}

LoadGameController::~LoadGameController(void)
{
}

void LoadGameController::update(float delta)
{
	int previousPercent = _loadGameControllerView->getPercentage();
	_loadGameControllerView->setPercentage(previousPercent + 1);
}

void LoadGameController::onEnterTransitionDidFinish()
{
	this->scheduleUpdate();
}