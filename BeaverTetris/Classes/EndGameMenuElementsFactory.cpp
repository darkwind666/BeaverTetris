#include "EndGameMenuElementsFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "EndGameMenuElementsCollectionCreator.h"
#include "GameViewElementsKeys.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;
using namespace std;

EndGameMenuElementsFactory::EndGameMenuElementsFactory(void)
{
	_endGameMenuElementsCreator = new EndGameMenuElementsCollectionCreator();
}


EndGameMenuElementsFactory::~EndGameMenuElementsFactory(void)
{
	delete _endGameMenuElementsCreator;
}

Node* EndGameMenuElementsFactory::getEndGameView()
{
	Node *endGameView = Node::create();
	makePopUpBeaverOnView(endGameView);
	makePopUpMenuOnView(endGameView);
	string endGameViewName = getEndGameViewName();
	endGameView->setName(endGameViewName);
	return endGameView;
}

void EndGameMenuElementsFactory::makePopUpBeaverOnView(Node *aView)
{
	Node *endGameBeaver = getEndGameBeaver();
	string key = endGameBeaver->getName();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(endGameBeaver, aView, key);
}

Node* EndGameMenuElementsFactory::getEndGameBeaver()
{
	string endGameBeaverName = getEndGameBeaverName();
	Sprite *endGameBeaver = CocosNodesHelper::getSpriteWithKey(endGameBeaverName);
	endGameBeaver->setName(endGameBeaverName);
	return endGameBeaver;
}

string EndGameMenuElementsFactory::getEndGameBeaverName()
{
	string endGameBeaverName = mainGameEndPopResultLoseImageKey;
	WinGameSystem *winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	if (winGameSystem->playerWin())
	{
		endGameBeaverName = mainGameEndPopResultWinImageKey;
	}
	return endGameBeaverName;
}

void EndGameMenuElementsFactory::makePopUpMenuOnView(Node *aView)
{
	Sprite *popUpPad = CocosNodesHelper::getSpriteWithKey(mainGameEndPopUpPadKey);
	vector<Node*> endGameViewElements = getEndGameViewElements();
	vector<Node*>::iterator elementsIterator;
	for (elementsIterator = endGameViewElements.begin(); elementsIterator != endGameViewElements.end(); elementsIterator++)
	{
		Node *viewElement = *elementsIterator;
		string elementKey = viewElement->getName();
		CocosNodesHelper::addChildNodeToParentNodeWithKey(viewElement, popUpPad, elementKey);
	}
	CocosNodesHelper::addChildNodeToParentNodeWithKey(popUpPad, aView, mainGameEndPopUpPadKey);
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
		endGameViewElements = _endGameMenuElementsCreator->getLoseGameElements();
	}
	return endGameViewElements;
}

vector<Node*> EndGameMenuElementsFactory::getWinGameElements()
{
	vector<Node*> winGameElements;
	CurrentLevelDataSource *currentLevelDataSource = (CurrentLevelDataSource*)ServiceLocator::getServiceForKey(currentLevelDataSourceKey);
	if (currentLevelDataSource->finalLevel())
	{
		winGameElements = _endGameMenuElementsCreator->getFinalLevelElements();
	}
	else
	{
		winGameElements = _endGameMenuElementsCreator->getNextLevelElements();
	}
	return winGameElements;
}

string EndGameMenuElementsFactory::getEndGameViewName()
{
	string endGameViewName = mainGameEndPopUpLoseViewKey;
	WinGameSystem *winGameSystem = (WinGameSystem*)ServiceLocator::getServiceForKey(winGameSystemKey);
	if (winGameSystem->playerWin())
	{
		endGameViewName = mainGameEndPopUpWinViewKey;
	}
	return endGameViewName;
}