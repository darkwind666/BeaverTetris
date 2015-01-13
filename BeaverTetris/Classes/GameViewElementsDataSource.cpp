#include "GameViewElementsDataSource.h"
#include "GameViewInformationFactory.h"
#include "GameViewConstants.h"
#include "GameFileExtensionMaker.h"

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
	Vec2 relativeElementPosition = Vec2( positionInDesignResolution.x / designResolutionWidth, positionInDesignResolution.y / designResolutionHeight);
	Size currentScreenSize = CCDirector::getInstance()->getWinSize();
	Vec2 absoluteElementPosition = Vec2(currentScreenSize.width * relativeElementPosition.x, currentScreenSize.height * relativeElementPosition.y);
	return absoluteElementPosition;
}

std::string GameViewElementsDataSource::getElementImageForKey(std::string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey);
}

int GameViewElementsDataSource::getElementZOrderForKey(std::string aKey)
{
	ViewElementInformation elementsInformation = _gameViewInformationFactory->getViewInformationForKey(aKey);
	return elementsInformation.elementZOrder;
}
