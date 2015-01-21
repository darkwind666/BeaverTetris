#include "GameWorldBackgroundController.h"
#include "MainGameBackgroundDataSource.h"

using namespace cocos2d;

GameWorldBackgroundController::GameWorldBackgroundController(void)
{
	_mainGameBackgroundDataSource = new MainGameBackgroundDataSource();
	makeControllerView();
}


GameWorldBackgroundController::~GameWorldBackgroundController(void)
{
}

void GameWorldBackgroundController::makeControllerView()
{
	LayerColor *backgroundView = LayerColor::create(Color4B::ORANGE);
	backgroundView->ignoreAnchorPointForPosition(false);
	this->addChild(backgroundView);
}