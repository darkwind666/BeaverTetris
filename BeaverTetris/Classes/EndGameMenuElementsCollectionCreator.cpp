#include "EndGameMenuElementsCollectionCreator.h"
#include "EndGameMenuElementCreator.h"
#include "GameLocalizationKeys.h"
#include "GameViewElementsKeys.h"

using namespace cocos2d;
using namespace std;

EndGameMenuElementsCollectionCreator::EndGameMenuElementsCollectionCreator(void)
{
	_endGameMenuElementCreator = new EndGameMenuElementCreator();
}


EndGameMenuElementsCollectionCreator::~EndGameMenuElementsCollectionCreator(void)
{
	delete _endGameMenuElementCreator;
}


vector<Node*> EndGameMenuElementsCollectionCreator::getFinalLevelElements()
{
	vector<Node*> finalLevelElements;
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithLocaleString(gameWinAllGameLocalizationKey);
	finalLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = _endGameMenuElementCreator->getPlayerAwardLabel();
	finalLevelElements.push_back(playerAwardLabel);

	Node *goToRecordsScreenButton = _endGameMenuElementCreator->getButtonWithCallbackAndKeyAndLocale(_endGameMenuElementCreator->getFinishGameCallback(), mainGameEndPopUpReplayLevelButtonKey, gameRecordsLocalizationKey);
	finalLevelElements.push_back(goToRecordsScreenButton);

	return finalLevelElements;
}

vector<Node*> EndGameMenuElementsCollectionCreator::getNextLevelElements()
{
	vector<Node*> nextLevelElements;
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithLocaleString(gameWinLocalizationKey);
	nextLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = _endGameMenuElementCreator->getPlayerAwardLabel();
	nextLevelElements.push_back(playerAwardLabel);

	Node *replayLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndKeyAndLocale(getGoToSceneCallback(kPlayGame), mainGameEndPopUpReplayLevelButtonKey, gameReplayLocalizationKey);
	nextLevelElements.push_back(replayLevelButton);

	Node *goToSelectLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndKeyAndLocale(getGoToSceneCallback(kSelectLevel), mainGamePauseGoToSelectLevelButtonKey, gameGoToMapLocalizationKey);
	nextLevelElements.push_back(goToSelectLevelButton);

	return nextLevelElements;
}

vector<Node*> EndGameMenuElementsCollectionCreator::getLoseGameElements()
{
	vector<Node*> loseGameElements;
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithLocaleString(gameLoseLocalizationKey);
	loseGameElements.push_back(gameStateLabel);

	Node *replayLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndKeyAndLocale(getGoToSceneCallback(kPlayGame), mainGameEndPopUpReplayLevelButtonKey, gameReplayLocalizationKey);
	loseGameElements.push_back(replayLevelButton);
	
	Node *goToSelectLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndKeyAndLocale(getGoToSceneCallback(kSelectLevel), mainGamePauseGoToSelectLevelButtonKey, gameGoToMapLocalizationKey);
	loseGameElements.push_back(goToSelectLevelButton);

	return loseGameElements;
}

ccMenuCallback EndGameMenuElementsCollectionCreator::getGoToSceneCallback(GameState aState)
{
	return _endGameMenuElementCreator->getGoToSceneCallback(aState);
}