#include "GameAnalyticController.h"
#include "cocos2d.h"
#include "GoogleAnalyticIndicatorsDataSource.h"

using namespace std;
using namespace cocos2d;

GameAnalyticController::GameAnalyticController(void)
{
	_indicatorsNamesDataSource = new GoogleAnalyticIndicatorsDataSource();
}


GameAnalyticController::~GameAnalyticController(void)
{
	endGame();
	delete _indicatorsNamesDataSource;
}

void GameAnalyticController::createdNewPlayerWithName(string aName)
{

}

void GameAnalyticController::winAllGameWithResult(int aResult)
{

}

void GameAnalyticController::winSelectedLevel()
{

}

void GameAnalyticController::loseSelectedLevel()
{

}

void GameAnalyticController::useSpell(std::string aSpellKey)
{

}

void GameAnalyticController::goToPopUp(PopUpType aPopUp)
{

}

void GameAnalyticController::goToScreen(GameState aScreen)
{

}

void GameAnalyticController::endGame()
{

}

