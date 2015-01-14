#include "GameViewInformationFactory.h"

#include <string>
#include "GameViewElementsKeys.h"
#include "GameViewConstants.h"
#include "GameViewElementsZOrders.h"

using namespace std;
using namespace cocos2d;

GameViewInformationFactory::GameViewInformationFactory(void)
{
	_elementsInformation =  map <string , ViewElementInformation> ();
	makeViewData();
}


GameViewInformationFactory::~GameViewInformationFactory(void)
{
	_elementsInformation.clear();
}

ViewElementInformation GameViewInformationFactory::getViewInformationForKey(string aKey)
{
	return _elementsInformation[aKey];
}

void GameViewInformationFactory::makeViewData() 
{
	
	makeLoadingScreenData();
	makeStartGameSreenData();
	makeSelectGameLevelScreenData();
	makeMainGameScreenData();
	makeRecordsScreenData();
	makeDevelopersScreenData();

}

void GameViewInformationFactory::makeLoadingScreenData()
{
	ViewElementInformation loadingScreenBackground;
	loadingScreenBackground.elementPosition = getScreenCenter();
	loadingScreenBackground.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[loadingGameBackgroundKey] = loadingScreenBackground;
	
	ViewElementInformation loadingBeaver;
	loadingBeaver.elementPosition = Vec2(130, 200);
	loadingBeaver.elementZOrder = kLoadingBeaverZOrder;
	_elementsInformation[loadingGameBeaverKey] = loadingBeaver;
	
	ViewElementInformation loadingClock;
	loadingClock.elementPosition = Vec2(350, 630);
	loadingClock.elementZOrder = kLoadingClockZOrder;
	_elementsInformation[loadingGameClockKey] = loadingClock;
}

void GameViewInformationFactory::makeStartGameSreenData()
{
	ViewElementInformation startGameScreenBackground;
	startGameScreenBackground.elementPosition = getScreenCenter();
	startGameScreenBackground.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[startGameMenuBackgroundKey] = startGameScreenBackground;

	ViewElementInformation startGameBeaver;
	startGameBeaver.elementPosition = Vec2(130, 200);
	startGameBeaver.elementZOrder = kStartGameBeaverZOrder;
	_elementsInformation[startGameBeaverKey] = startGameBeaver;

	ViewElementInformation startGameMenu;
	startGameMenu.elementPosition = Vec2(80, 400);
	startGameMenu.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[startGameMenuKey] = startGameMenu;
}

void GameViewInformationFactory::makeSelectGameLevelScreenData()
{

}

void GameViewInformationFactory::makeMainGameScreenData()
{

}

void GameViewInformationFactory::makeRecordsScreenData()
{

}

void GameViewInformationFactory::makeDevelopersScreenData()
{

}


Vec2 GameViewInformationFactory::getScreenCenter()
{
	return Vec2(designResolutionWidth/2, designResolutionHeight/2);
}



