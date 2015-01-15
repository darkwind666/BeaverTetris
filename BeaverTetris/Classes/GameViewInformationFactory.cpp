#include "GameViewInformationFactory.h"

#include <string>
#include "GameFileExtensionMaker.h"

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
	makeStartGameRegulateSoundPopUpData();
	makeSelectGameLevelScreenData();
	makeMainGameScreenData();
	makeRecordsScreenData();
	makeDevelopersScreenData();

}

void GameViewInformationFactory::makeLoadingScreenData()
{
	ViewElementInformation loadingScreenBackground;
	loadingScreenBackground.elementImage = getImageNameForKey(loadingGameBackgroundKey);
	loadingScreenBackground.elementPosition = getScreenCenter();
	loadingScreenBackground.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[loadingGameBackgroundKey] = loadingScreenBackground;
	
	ViewElementInformation loadingBeaver;
	loadingBeaver.elementImage = getImageNameForKey(loadingGameBeaverKey);
	loadingBeaver.elementPosition = Vec2(130, 200);
	loadingBeaver.elementZOrder = kLoadingBeaverZOrder;
	_elementsInformation[loadingGameBeaverKey] = loadingBeaver;
	
	ViewElementInformation loadingClock;
	loadingClock.elementImage = getImageNameForKey(loadingGameClockKey);
	loadingClock.elementPosition = Vec2(350, 630);
	loadingClock.elementZOrder = kLoadingClockZOrder;
	_elementsInformation[loadingGameClockKey] = loadingClock;
}

void GameViewInformationFactory::makeStartGameSreenData()
{
	ViewElementInformation startGameScreenBackground;
	startGameScreenBackground.elementImage = getImageNameForKey(startGameMenuBackgroundKey);
	startGameScreenBackground.elementPosition = getScreenCenter();
	startGameScreenBackground.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[startGameMenuBackgroundKey] = startGameScreenBackground;

	ViewElementInformation startGameMenu;
	startGameMenu.elementPosition = Vec2(80, 800);
	startGameMenu.elementActionFinalPosition = Vec2(80, 400);
	startGameMenu.elementOffset = Vec2(0, 85);
	startGameMenu.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[startGameMenuKey] = startGameMenu;

	ViewElementInformation startGameBeaver;
	startGameBeaver.elementImage = getImageNameForKey(startGameBeaverKey);
	startGameBeaver.elementPosition = Vec2(480, 0);
	startGameBeaver.elementActionFinalPosition = Vec2(200, 200);
	startGameBeaver.elementOffset = Vec2(0, 200);
	startGameBeaver.elementZOrder = kStartGameBeaverZOrder;
	_elementsInformation[startGameBeaverKey] = startGameBeaver;
	
	ViewElementInformation beaverClockArrow;
	beaverClockArrow.elementImage = getImageNameForKey(startGameBeaverClockKey);
	beaverClockArrow.elementPosition = Vec2(100, 350);
	beaverClockArrow.elementZOrder = kBeaverClockArrowZOrder;
	_elementsInformation[startGameBeaverClockKey] = beaverClockArrow;

}

void GameViewInformationFactory::makeStartGameRegulateSoundPopUpData()
{
	ViewElementInformation startGameRegulateSoundPopUp;
	startGameRegulateSoundPopUp.elementPosition = Vec2(0, 0);
	startGameRegulateSoundPopUp.elementActionFinalPosition = getScreenCenter();
	startGameRegulateSoundPopUp.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameRegulateSoundPopUpKey] = startGameRegulateSoundPopUp;

	ViewElementInformation startGameRegulateSoundPopUpPad;
	startGameRegulateSoundPopUpPad.elementImage = getImageNameForKey(startGameRegulateSoundPadKey);
	startGameRegulateSoundPopUpPad.elementPosition = Vec2(getScreenCenterX(), 650);
	startGameRegulateSoundPopUpPad.elementActionFinalPosition = getScreenCenter();
	startGameRegulateSoundPopUpPad.elementZOrder = kStartGameRegulateSoundPopUpPadZOrder;
	_elementsInformation[startGameRegulateSoundPadKey] = startGameRegulateSoundPopUpPad;

	ViewElementInformation startGameRegulateSoundSlider;
	startGameRegulateSoundSlider.elementImage = getImageNameForKey(startGameRegulateSoundSliderKey);
	startGameRegulateSoundSlider.elementPosition = Vec2(90, 160);
	startGameRegulateSoundSlider.elementZOrder = kStartGameRegulateSoundSliderZOrder;
	_elementsInformation[startGameRegulateSoundSliderKey] = startGameRegulateSoundSlider;

	ViewElementInformation startGameRegulateSoundEffectsSlider;
	startGameRegulateSoundEffectsSlider.elementImage = getImageNameForKey(startGameRegulateSoundEffectsSliderKey);
	startGameRegulateSoundEffectsSlider.elementPosition = Vec2(90, 120);
	startGameRegulateSoundEffectsSlider.elementZOrder = kStartGameRegulateSoundEffectsSliderZOrder;
	_elementsInformation[startGameRegulateSoundEffectsSliderKey] = startGameRegulateSoundEffectsSlider;

	ViewElementInformation startGameRegulateSoundCloseButton;
	startGameRegulateSoundCloseButton.elementImage = getImageNameForKey(startGameRegulateSoundCloseButtonKey);
	startGameRegulateSoundCloseButton.elementPosition = Vec2(150, 50);
	startGameRegulateSoundCloseButton.elementZOrder = kStartGameRegulateSoundPopUpCloseButtonZOrder;
	_elementsInformation[startGameRegulateSoundCloseButtonKey] = startGameRegulateSoundCloseButton;
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
	return Vec2(getScreenCenterX(), getScreenCenterY());
}

float GameViewInformationFactory::getScreenCenterX()
{
	return designResolutionWidth/2;
}

float GameViewInformationFactory::getScreenCenterY()
{
	return designResolutionHeight/2;
}

string GameViewInformationFactory::getImageNameForKey(string aKey)
{
	return GameFileExtensionMaker::getGraphicWithExtension(aKey);
}


