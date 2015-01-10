#include "GameViewInformationFactory.h"

#include <string>
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"

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

	ViewElementInformation viewElement1;
	viewElement1.elementPosition = Vec2(10, 10);
	viewElement1.elementZOrder = 3;
	viewElementsInformation[gameElement1Key] = viewElement1;

	return viewElementsInformation;
}



