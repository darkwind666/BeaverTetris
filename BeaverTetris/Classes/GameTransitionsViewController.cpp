#include "GameTransitionsViewController.h"
#include "ScenesFactory.h"
#include "GameViewConstants.h"

using namespace std;
using namespace cocos2d;

GameTransitionsViewController::GameTransitionsViewController()
{
	_scenesFactory = new ScenesFactory();
}

GameTransitionsViewController::~GameTransitionsViewController(void)
{
}

void GameTransitionsViewController::goToInitialState(void)
{
	CCScene *sceneWithTransition = getSceneWithTransitionForId(kLoadGame);
	CCDirector *director = CCDirector::getInstance();
	director->runWithScene(sceneWithTransition);
}

void GameTransitionsViewController::changeOnNewState(GameState aNewGameState)
{
	CCScene *sceneWithTransition = getSceneWithTransitionForId(aNewGameState);
	CCDirector *director = CCDirector::getInstance();
	director->replaceScene(sceneWithTransition);
}

CCScene* GameTransitionsViewController::getSceneWithTransitionForId(GameState aSceneId)
{
	CCScene *startScene = _scenesFactory->getGameSceneForId(aSceneId);
	CCScene *sceneWithTransition = getSceneWithStandartTransition(startScene);
	return sceneWithTransition;
}

CCScene* GameTransitionsViewController::getSceneWithStandartTransition(CCScene* aScene)
{
	return CCTransitionFade::create(standartTransitionDuration, aScene);
}