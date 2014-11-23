#include "GameViewInformationFactory.h"

#include <string>
#include "GameElementsKeys.h"
#include "GameResourcesExtension.h"

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

void GameViewInformationFactory::setGameElementsInformationInDataSource(GameViewElementsDataSource aDataSource) 
{

}

std::map <std::string , ViewElementInformation> GameViewInformationFactory::makeViewData() 
{

	ViewElementInformation viewElement1;
	viewElement1.elementImage =  makeImageNameWithKey(gameElement1Key);
	viewElement1.elementPosition = Vec2(10, 10);
	viewElement1.elementZOrder = 3;


	std::map <std::string , ViewElementInformation> viewElementsInformation;
	viewElementsInformation[gameElement1Key] = viewElement1;

}

string GameViewInformationFactory::makeImageNameWithKey(const string gameElementKey) 
{
	string imageNameWithExtansion = gameElementKey + graphicFileExtension;
	return imageNameWithExtansion;
}


