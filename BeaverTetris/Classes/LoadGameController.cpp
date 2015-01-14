#include "LoadGameController.h"
#include "LoadingGameDataSource.h"
#include "GameViewConstants.h"
#include "GameStatesHelper.h"

using namespace std;
using namespace cocos2d;

LoadGameController::LoadGameController(void)
{
	CCSprite *sourceView = CCSprite::create("HelloWorld.png");
	_loadGameControllerView =  CCProgressTimer::create(sourceView);
	_loadGameControllerView->setPercentage(0);
	_loadGameControllerView->setScale(0.7f);
	this->addChild(_loadGameControllerView);

	_loadingGameDataSource = new LoadingGameDataSource();
	_loadedResourcesCount = 0;

}

LoadGameController::~LoadGameController(void)
{
}

void LoadGameController::onEnterTransitionDidFinish()
{
	loadGameResource();
}

void LoadGameController::loadGameResource()
{
	int resourcesCount = _loadingGameDataSource->getResourcesCount();

	if (_loadedResourcesCount < resourcesCount)
	{
		loadOneResource();
	}
	else
	{
		GameStatesHelper::goToScene(kStartGame);
	}

}

void LoadGameController::loadOneResource()
{
	int loadingPercent = _loadingGameDataSource->getResourceLoadingPercentForIndex(_loadedResourcesCount);
	_loadingGameDataSource->loadResouceForIndex(_loadedResourcesCount);
	_loadedResourcesCount++;
	runLoadingActionWithLoadingPercent(loadingPercent);
}

void LoadGameController::runLoadingActionWithLoadingPercent(int aLoadingPercent)
{
	int currentPercent = _loadGameControllerView->getPercentage();
	float actionDuration = onePercentActionDuration * aLoadingPercent;
	
	CCFiniteTimeAction *progressAction = CCProgressFromTo::create(actionDuration, currentPercent, currentPercent + aLoadingPercent);
	CCFiniteTimeAction *callback = CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(LoadGameController::loadGameResource));
	CCAction *sequence = CCSequence::create(progressAction, callback, NULL);
	_loadGameControllerView->runAction(sequence);
}