#include "MainGameEndPopUp.h"
#include <vector>
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "EndGameMenuElementsFactory.h"
#include "GameWorldController.h"
#include "GameHudsController.h"
#include "MainGameEndPopUpSoundController.h"

using namespace cocos2d;
using namespace std;

MainGameEndPopUp::MainGameEndPopUp(GameWorldController *aGameWorldController, GameHudsController *aGameHudsController)
{
	ScreenPopUp::subscribePopUpToMessage(this, kEndGamePopUp);
	_gameWorldController = aGameWorldController;
	_gameHudsController = aGameHudsController;
	_mainGameEndPopUpSoundController = new MainGameEndPopUpSoundController();
	_popUpView = GameViewStyleHelper::getPopUpBackground();
	_popUpView->setVisible(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(_popUpView,this,mainGameEndPopUpBackgroundKey);
}


MainGameEndPopUp::~MainGameEndPopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kEndGamePopUp);
	delete _mainGameEndPopUpSoundController;
}

void MainGameEndPopUp::showPopUp()
{
	_gameWorldController->pauseGameWorld();
	_gameHudsController->pauseHuds();
	fillViewWithElements();
	_mainGameEndPopUpSoundController->playEndGameSound();
	_popUpView->setVisible(true);
}

void MainGameEndPopUp::fillViewWithElements()
{
	EndGameMenuElementsFactory endGameMenuElementsFactory;
	Node *endGameView = endGameMenuElementsFactory.getEndGameView();
	string key = endGameView->getName();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(endGameView, _popUpView, key);
}

void MainGameEndPopUp::onExitTransitionDidStart()
{
	_mainGameEndPopUpSoundController->stopPlayingSound();
}