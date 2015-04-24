#include "GameHudsController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "PlayerActionControllerFactory.h"
#include "MainGamePlayerScoreController.h"
#include "MainGameVictoryConditionController.h"
#include "PlayerSpellsControllerFactory.h"
#include "MainGamePauseViewController.h"

using namespace cocos2d;

GameHudsController::GameHudsController(void)
{
	makeView();
}


GameHudsController::~GameHudsController(void)
{
}

void GameHudsController::makeView()
{
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, gameHudBackgroundKey);

	PlayerActionControllerFactory playerActionControllerFactory;
	Node *playerActionController = playerActionControllerFactory.getPlayerActionControllerForCurrentPlatform();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(playerActionController, this, playerActionControllerKey);

	MainGamePlayerScoreController *playerScoreController = new MainGamePlayerScoreController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(playerScoreController, this, playerScoreControllerKey);
	_playerScoreController = playerScoreController;

	MainGameVictoryConditionController *victoryConditionController = new MainGameVictoryConditionController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(victoryConditionController, this, victoryConditionHudControllerKey);
	_victoryConditionController = victoryConditionController;

	PlayerSpellsControllerFactory playerSpellsControllerFactory;
	Node *playerSpellsController = playerSpellsControllerFactory.getPlayerSpellsControllerForCurrentPlatform();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(playerSpellsController, this, playerSpellsControllerKey);
	_playerSpellsController = playerSpellsController;

	MainGamePauseViewController *mainGamePauseViewController = new MainGamePauseViewController();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(mainGamePauseViewController, this, pauseGameViewControllerKey);

}

void GameHudsController::onEnterTransitionDidFinish()
{
	scheduleUpdate();
}

void GameHudsController::update(float delta)
{
	_playerScoreController->update(delta);
	_victoryConditionController->update(delta);
	_playerSpellsController->update(delta);
}

void GameHudsController::pauseHuds()
{
	unscheduleUpdate();
}

void GameHudsController::resumeHuds()
{
	scheduleUpdate();
}