#include "EndGameMenuElementsCollectionCreator.h"
#include "EndGameMenuElementCreator.h"

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
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithString(string("You win all game!"));
	finalLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = _endGameMenuElementCreator->getPlayerAwardLabel();
	finalLevelElements.push_back(playerAwardLabel);

	function<void()> aCallback = [](){};
	Node *goToRecordsScreenButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(aCallback, ccColor3B::GREEN);
	finalLevelElements.push_back(goToRecordsScreenButton);

	return finalLevelElements;
}

vector<Node*> EndGameMenuElementsCollectionCreator::getNextLevelElements()
{
	vector<Node*> nextLevelElements;
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithString(string("You win!"));
	nextLevelElements.push_back(gameStateLabel);

	Node *playerAwardLabel = _endGameMenuElementCreator->getPlayerAwardLabel();
	nextLevelElements.push_back(playerAwardLabel);

	Node *nextLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(_endGameMenuElementCreator->getNextLevelCallback(), ccColor3B::YELLOW);
	nextLevelElements.push_back(nextLevelButton);

	Node *replayLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(getGoToSceneCallback(kPlayGame), ccColor3B::GRAY);
	nextLevelElements.push_back(replayLevelButton);

	Node *goToSelectLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(getGoToSceneCallback(kSelectLevel), ccColor3B::MAGENTA);
	nextLevelElements.push_back(goToSelectLevelButton);

	return nextLevelElements;
}

vector<Node*> EndGameMenuElementsCollectionCreator::getLoseGameElements()
{
	vector<Node*> loseGameElements;
	
	Node *gameStateLabel = _endGameMenuElementCreator->getGameStateLabelWithString(string("You lose!"));
	loseGameElements.push_back(gameStateLabel);

	Node *replayLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(getGoToSceneCallback(kPlayGame), ccColor3B::GRAY);
	loseGameElements.push_back(replayLevelButton);
	
	Node *goToSelectLevelButton = _endGameMenuElementCreator->getButtonWithCallbackAndColor(getGoToSceneCallback(kSelectLevel), ccColor3B::MAGENTA);
	loseGameElements.push_back(goToSelectLevelButton);

	return loseGameElements;
}

function<void()> EndGameMenuElementsCollectionCreator::getGoToSceneCallback(GameState aState)
{
	return _endGameMenuElementCreator->getGoToSceneCallback(aState);
}