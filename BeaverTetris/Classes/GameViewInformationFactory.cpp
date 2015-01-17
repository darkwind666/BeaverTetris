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
	makeSelectGameLevelMenuData();
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
	ViewElementInformation selectGameLevelMenu;
	selectGameLevelMenu.elementImage = getImageNameForKey(startGameRegulateSoundCloseButtonKey);
	selectGameLevelMenu.elementPosition = getScreenCenter();
	selectGameLevelMenu.elementZOrder = kSelectLevelMenuZOrder;
	_elementsInformation[selectLevelMenuKey] = selectGameLevelMenu;
	
}

void GameViewInformationFactory::makeSelectGameLevelMenuData()
{
	ViewElementInformation gameLevel1;
	gameLevel1.elementPosition = Vec2(50, 80);
	_elementsInformation[gameLevel1Key] = gameLevel1;

	ViewElementInformation gameLevel2;
	gameLevel2.elementPosition = Vec2(95, 200);
	_elementsInformation[gameLevel2Key] = gameLevel2;

	ViewElementInformation gameLevel3;
	gameLevel3.elementPosition = Vec2(250, 240);
	_elementsInformation[gameLevel3Key] = gameLevel3;

	ViewElementInformation gameLevel4;
	gameLevel4.elementPosition = Vec2(210, 330);
	_elementsInformation[gameLevel4Key] = gameLevel4;

	ViewElementInformation gameLevel5;
	gameLevel5.elementPosition = Vec2(56, 450);
	_elementsInformation[gameLevel5Key] = gameLevel5;

	ViewElementInformation gameLevel6;
	gameLevel6.elementPosition = Vec2(143, 530);
	_elementsInformation[gameLevel6Key] = gameLevel6;

	ViewElementInformation gameLevel7;
	gameLevel7.elementPosition = Vec2(230, 620);
	_elementsInformation[gameLevel7Key] = gameLevel7;

	ViewElementInformation gameLevel8;
	gameLevel8.elementPosition = Vec2(93, 660);
	_elementsInformation[gameLevel8Key] = gameLevel8;

	ViewElementInformation gameLevel9;
	gameLevel9.elementPosition = Vec2(267, 730);
	_elementsInformation[gameLevel9Key] = gameLevel9;

	ViewElementInformation gameLevel10;
	gameLevel10.elementPosition = Vec2(170, 800);
	_elementsInformation[gameLevel10Key] = gameLevel10;

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


