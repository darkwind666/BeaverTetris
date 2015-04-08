#include "GameTransitionsViewController.h"
#include "ScenesFactory.h"
#include "GameAnimationActionsConstants.h"

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
	Scene *sceneWithTransition = getSceneWithTransitionForId(kLoadGame);
	Director *director = Director::getInstance();
	director->runWithScene(sceneWithTransition);
}

void GameTransitionsViewController::changeOnNewState(GameState aNewGameState)
{
	Scene *sceneWithTransition = getSceneWithTransitionForId(aNewGameState);
	Director *director = Director::getInstance();
	director->replaceScene(sceneWithTransition);
}

Scene* GameTransitionsViewController::getSceneWithTransitionForId(GameState aSceneId)
{
	Scene *startScene = _scenesFactory->getGameSceneForId(aSceneId);
	Scene *sceneWithTransition = getSceneWithStandartTransition(startScene);
	return sceneWithTransition;
}

Scene* GameTransitionsViewController::getSceneWithStandartTransition(Scene* aScene)
{
	return TransitionFade::create(standartTransitionDuration, aScene);
}