#include "GameViewInformationFactory.h"

#include <string>
#include "GameViewElementsKeys.h"
#include "GameViewConstants.h"
#include "GameViewElementsZOrders.h"

using namespace std;
using namespace cocos2d;

GameViewInformationFactory::GameViewInformationFactory(void)
{
	_elementsInformation =  makeViewData();
}


GameViewInformationFactory::~GameViewInformationFactory(void)
{
	_elementsInformation.clear();
}

ViewElementInformation GameViewInformationFactory::getViewInformationForKey(string aKey)
{
	return _elementsInformation[aKey];
}

map <string , ViewElementInformation> GameViewInformationFactory::makeViewData() 
{
	
	std::map <std::string , ViewElementInformation> viewElementsInformation;

	ViewElementInformation loadingScreenBackground;
	loadingScreenBackground.elementPosition = getScreenCenter();
	loadingScreenBackground.elementZOrder = kLoadingBackgroundZOrder;
	viewElementsInformation[loadingGameBackgroundKey] = loadingScreenBackground;

	ViewElementInformation loadingBeaver;
	loadingBeaver.elementPosition = Vec2(130, 200);
	loadingBeaver.elementZOrder = kLoadingBeaverZOrder;
	viewElementsInformation[loadingGameBeaverKey] = loadingBeaver;

	ViewElementInformation loadingClock;
	loadingClock.elementPosition = Vec2(150, 300);
	loadingClock.elementZOrder = kLoadingClockZOrder;
	viewElementsInformation[loadingGameClockKey] = loadingClock;

	return viewElementsInformation;
}

Vec2 GameViewInformationFactory::getScreenCenter()
{
	return Vec2(designResolutionWidth/2, designResolutionHeight/2);
}



