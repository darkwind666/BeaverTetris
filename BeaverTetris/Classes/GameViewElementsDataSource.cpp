#include "GameViewElementsDataSource.h"
#include "GameViewInformationFactory.h"
#include "GameViewConstants.h"

using namespace cocos2d;

GameViewElementsDataSource::GameViewElementsDataSource(void)
{
	 _gameViewInformationFactory = new GameViewInformationFactory();
}


GameViewElementsDataSource::~GameViewElementsDataSource(void)
{
}


Vec2 GameViewElementsDataSource::getElementPositionForKey(std::string aKey) 
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	Vec2 positionInDesignResolution = elementsInformation.elementPosition;
	Vec2 absoluteElementPosition = getAbsolutePosition(positionInDesignResolution);
	return absoluteElementPosition;
}

std::string GameViewElementsDataSource::getElementImageForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	return elementsInformation.elementImage;
}

int GameViewElementsDataSource::getElementZOrderForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	return elementsInformation.elementZOrder;
}

Vec2 GameViewElementsDataSource::getElementOffsetForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	Vec2 offsetInDesignResolution = elementsInformation.elementOffset;
	Vec2 absoluteElementOffset = getAbsolutePosition(offsetInDesignResolution);
	return absoluteElementOffset;
}

Vec2 GameViewElementsDataSource::getElementFinalActionPositionForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	Vec2 finalActionPositionInDesignResolution = elementsInformation.elementActionFinalPosition;
	Vec2 absoluteActionPosition = getAbsolutePosition(finalActionPositionInDesignResolution);
	return absoluteActionPosition;
}

Vec2 GameViewElementsDataSource::getAbsolutePosition(cocos2d::Vec2 aDesignPosition)
{
	Vec2 relativeElementPosition = Vec2( aDesignPosition.x / designResolutionWidth, aDesignPosition.y / designResolutionHeight);
	Size currentScreenSize = CCDirector::getInstance()->getWinSize();
	Vec2 absoluteElementPosition = Vec2(currentScreenSize.width * relativeElementPosition.x, currentScreenSize.height * relativeElementPosition.y);
	return absoluteElementPosition;
}