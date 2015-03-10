#include "EndGameMenuElementsFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "GameViewStyleHelper.h"
#include "GameStatesHelper.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"

using namespace cocos2d;
using namespace std;

EndGameMenuElementsFactory::EndGameMenuElementsFactory(void)
{
}


EndGameMenuElementsFactory::~EndGameMenuElementsFactory(void)
{
}

vector<Node*> EndGameMenuElementsFactory::getEndGameViewElements()
{
	vector<Node*> endGameViewElements;
	WinGameSystem *winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	if (winGameSystem->playerWin())
	{
		endGameViewElements = getWinGameElements();
	}
	else
	{
		endGameViewElements = getLoseGameElements();
	}
	return endGameViewElements;
}

vector<Node*> EndGameMenuElementsFactory::getWinGameElements()
{
	vector<Node*> winGameElements;
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	if (currentLevelDataSource->finalLevel())
	{
		winGameElements = getFinalLevelElements();
	}
	else
	{
		winGameElements = getNextLevelElements();
	}
	return winGameElements;
}

vector<Node*> EndGameMenuElementsFactory::getFinalLevelElements()
{
	vector<Node*> finalLevelElements;
	
	Node *gameStateLabel = getGameStateLabelWithString(string("You win all game!"));
	finalLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = getPlayerAwardLabel();
	finalLevelElements.push_back(playerAwardLabel);

	function<void()> aCallback = [](){};
	Node *goToRecordsScreenButton = getButtonWithCallbackAndColor(aCallback, ccColor3B::GREEN);
	finalLevelElements.push_back(goToRecordsScreenButton);

	return finalLevelElements;
}

vector<Node*> EndGameMenuElementsFactory::getNextLevelElements()
{
	vector<Node*> nextLevelElements;
	
	Node *gameStateLabel = getGameStateLabelWithString(string("You win!"));
	nextLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = getPlayerAwardLabel();
	nextLevelElements.push_back(playerAwardLabel);

	Node *nextLevelButton = getButtonWithCallbackAndColor(getNextLevelCallback(), ccColor3B::YELLOW);
	nextLevelElements.push_back(nextLevelButton);

	Node *replayLevelButton = getButtonWithCallbackAndColor(getGoToSceneCallback(kPlayGame), ccColor3B::GRAY);
	nextLevelElements.push_back(replayLevelButton);

	Node *goToSelectLevelButton = getButtonWithCallbackAndColor(getGoToSceneCallback(kSelectLevel), ccColor3B::MAGENTA);
	nextLevelElements.push_back(goToSelectLevelButton);

	return nextLevelElements;
}

vector<Node*> EndGameMenuElementsFactory::getLoseGameElements()
{
	vector<Node*> loseGameElements;
	
	Node *gameStateLabel = getGameStateLabelWithString(string("You lose!"));
	loseGameElements.push_back(gameStateLabel);

	Node *replayLevelButton = getButtonWithCallbackAndColor(getGoToSceneCallback(kPlayGame), ccColor3B::GRAY);
	loseGameElements.push_back(replayLevelButton);
	
	Node *goToSelectLevelButton = getButtonWithCallbackAndColor(getGoToSceneCallback(kSelectLevel), ccColor3B::MAGENTA);
	loseGameElements.push_back(goToSelectLevelButton);

	return loseGameElements;
}

Node* EndGameMenuElementsFactory::getGameStateLabelWithString(string stateLabelString)
{
	LabelTTF *gameState = GameViewStyleHelper::getStandardLabel();
	gameState->setFontSize(20);
	gameState->setString(stateLabelString);
	return gameState;
}

Node* EndGameMenuElementsFactory::getButtonWithCallbackAndColor(function<void()> aCallback, cocos2d::ccColor3B aColor)
{
	CCMenuItemImage *button = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png");
	button->setScaleX(0.2f);
	button->setScaleY(0.07f);
	button->setColor(aColor);
	button->setCallback([aCallback](Ref *sender){
		Node *button = (Node*)sender;
		GameViewStyleHelper::runStandardButtonActionWithCallback(button, aCallback);
	});
	CCMenu *menuForButton = CCMenu::create();
	menuForButton->addChild(button);
	return menuForButton;
}

Node* EndGameMenuElementsFactory::getPlayerAwardLabel()
{
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	int playerAward = currentLevelDataSource->getCurrentLevelData().levelAward;
	Node *playerAwardLabel = getGameStateLabelWithString(StringsSupporter::getStringFromNumber(playerAward));
	return playerAwardLabel;
}

function<void()> EndGameMenuElementsFactory::getNextLevelCallback()
{
	function<void()> nextLevelCallback = [](){
		CurrentPlayerDataSource *currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
		int currentLevelIndex = currentPlayerDataSource->getSelectedGameLevelIndex();
		currentPlayerDataSource->setSelectedGameLevelIndex(currentLevelIndex + 1);
		GameStatesHelper::goToScene(kPlayGame);
	};
	return nextLevelCallback;
}

function<void()> EndGameMenuElementsFactory::getGoToSceneCallback(GameState aState)
{
	function<void()> goToSceneCallback = [aState](){
		GameStatesHelper::goToScene(aState);
	};
	return goToSceneCallback;
}