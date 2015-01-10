#include "GameViewElementsDataSource.h"

GameViewElementsDataSource::GameViewElementsDataSource(void)
{
	 _elementsInformation = std::map < std::string,ViewElementInformation>();
}


GameViewElementsDataSource::~GameViewElementsDataSource(void)
{
	_elementsInformation.clear();
}


cocos2d::Vec2 GameViewElementsDataSource::getElementPositionForKey(std::string aKey) 
{
	ViewElementInformation elementsInformation = _elementsInformation[aKey];
	return elementsInformation.elementPosition;
}

std::string GameViewElementsDataSource::getElementImageForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _elementsInformation[aKey];
	return elementsInformation.elementImage;
}

int GameViewElementsDataSource::getElementZOrderForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _elementsInformation[aKey];
	return elementsInformation.elementZOrder;
}


void GameViewElementsDataSource::setViewStructureForKey(ViewElementInformation aElementInformation, std::string aKey)
{

	_elementsInformation[aKey] = aElementInformation;

}