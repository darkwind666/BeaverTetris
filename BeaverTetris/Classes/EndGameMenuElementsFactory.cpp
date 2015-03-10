#include "EndGameMenuElementsFactory.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "WinGameSystem.h"
#include "CurrentLevelDataSource.h"
#include "EndGameMenuElementsCollectionCreator.h"

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