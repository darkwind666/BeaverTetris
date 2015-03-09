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
	startGameMenu.elementPosition = Vec2(80, 850);
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

	ViewElementInformation startGameRegulateSoundPopUp;
	startGameRegulateSoundPopUp.elementPosition = Vec2(0, 0);
	startGameRegulateSoundPopUp.elementActionFinalPosition = getScreenCenter();
	startGameRegulateSoundPopUp.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameRegulateSoundPopUpKey] = startGameRegulateSoundPopUp;

	makeStartGameRegulateSoundPopUpData();

}

void GameViewInformationFactory::makeStartGameRegulateSoundPopUpData()
{

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
	selectGameLevelMenu.elementImage = getImageNameForKey(selectLevelMenuKey);
	selectGameLevelMenu.elementPosition = getScreenCenter();
	selectGameLevelMenu.elementZOrder = kSelectLevelMenuZOrder;
	_elementsInformation[selectLevelMenuKey] = selectGameLevelMenu;

	makeSelectGameLevelMenuData();

	ViewElementInformation selectGameLevelPlayerStatus;
	selectGameLevelPlayerStatus.elementImage = getImageNameForKey(selectLevelScenePlayerStatusControllerKey);
	selectGameLevelPlayerStatus.elementPosition = Vec2(0, 0);
	selectGameLevelPlayerStatus.elementZOrder = kSelectLevelScenePlayerStatusControllerZOrder;
	_elementsInformation[selectLevelScenePlayerStatusControllerKey] = selectGameLevelPlayerStatus;
	
	makeSelectGameLevelPlayerStatusData();

	ViewElementInformation playerCreatorController;
	playerCreatorController.elementImage = getImageNameForKey(playerCreatorControllerKey);
	playerCreatorController.elementPosition = Vec2(0, 0);
	playerCreatorController.elementZOrder = kPlayerCreatorControllerZOrder;
	_elementsInformation[playerCreatorControllerKey] = playerCreatorController;

	makeSelectGameLevelPlayerCreatorControllerData();

	ViewElementInformation selectLevelSceneBackButton;
	selectLevelSceneBackButton.elementImage = getImageNameForKey(playerCreatorControllerKey);
	selectLevelSceneBackButton.elementPosition = Vec2(70, 40);
	selectLevelSceneBackButton.elementZOrder = kSelectLevelSceneBackButtonZOrder;
	_elementsInformation[selectLevelSceneBackButtonKey] = selectLevelSceneBackButton;

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
	gameLevel5.elementPosition = Vec2(56, 430);
	_elementsInformation[gameLevel5Key] = gameLevel5;

	ViewElementInformation gameLevel6;
	gameLevel6.elementPosition = Vec2(143, 500);
	_elementsInformation[gameLevel6Key] = gameLevel6;

	ViewElementInformation gameLevel7;
	gameLevel7.elementPosition = Vec2(230, 570);
	_elementsInformation[gameLevel7Key] = gameLevel7;

	ViewElementInformation gameLevel8;
	gameLevel8.elementPosition = Vec2(93, 630);
	_elementsInformation[gameLevel8Key] = gameLevel8;

	ViewElementInformation gameLevel9;
	gameLevel9.elementPosition = Vec2(267, 680);
	_elementsInformation[gameLevel9Key] = gameLevel9;

	ViewElementInformation gameLevel10;
	gameLevel10.elementPosition = Vec2(130, 800);
	_elementsInformation[gameLevel10Key] = gameLevel10;

}

void GameViewInformationFactory::makeSelectGameLevelPlayerStatusData()
{
	ViewElementInformation selectGameLevelPlayerStatusPad;
	selectGameLevelPlayerStatusPad.elementImage = getImageNameForKey(selectLevelScenePlayerStatusControllerKey);
	selectGameLevelPlayerStatusPad.elementPosition = Vec2(240, 580);
	selectGameLevelPlayerStatusPad.elementActionFinalPosition = Vec2(240, 420);
	selectGameLevelPlayerStatusPad.elementZOrder = kSelectLevelPlayerStatusPadZOrder;
	_elementsInformation[selectLevelScenePlayerStatusPadKey] = selectGameLevelPlayerStatusPad;

	ViewElementInformation selectLevelScenePlayerStatusName;
	selectLevelScenePlayerStatusName.elementPosition = Vec2(240, 230);
	selectLevelScenePlayerStatusName.elementZOrder = kSelectLevelPlayerStatusNameZOrder;
	_elementsInformation[selectLevelScenePlayerStatusNameKey] = selectLevelScenePlayerStatusName;

	ViewElementInformation selectLevelScenePlayerStatusScore;
	selectLevelScenePlayerStatusScore.elementPosition = Vec2(240, 110);
	selectLevelScenePlayerStatusScore.elementZOrder = kSelectLevelPlayerStatusScoreZOrder;
	_elementsInformation[selectLevelScenePlayerStatusScoreKey] = selectLevelScenePlayerStatusScore;

}

void GameViewInformationFactory::makeSelectGameLevelPlayerCreatorControllerData()
{
	ViewElementInformation playerCreatorPad;
	playerCreatorPad.elementImage = getImageNameForKey(selectLevelScenePlayerStatusControllerKey);
	playerCreatorPad.elementPosition = Vec2(getScreenCenterX(), 560);
	playerCreatorPad.elementActionFinalPosition = getScreenCenter();
	playerCreatorPad.elementZOrder = kPlayerCreatorPadZOrder;
	_elementsInformation[playerCreatorControllerPadKey] = playerCreatorPad;

	ViewElementInformation playerCreatorText;
	playerCreatorText.elementPosition = Vec2(140, 110);
	playerCreatorText.elementZOrder = kPlayerCreatorTextZOrder;
	_elementsInformation[playerCreatorControllerTextKey] = playerCreatorText;

	ViewElementInformation playerCreatorInput;
	playerCreatorInput.elementPosition = Vec2(140, 50);
	playerCreatorInput.elementZOrder = kPlayerCreatorInputZOrder;
	_elementsInformation[playerCreatorControllerInputKey] = playerCreatorInput;

}

void GameViewInformationFactory::makeMainGameScreenData()
{
	ViewElementInformation mainGameWorldController;
	mainGameWorldController.elementPosition = Vec2(0, 0);
	mainGameWorldController.elementZOrder = kWorldControllerZOrder;
	_elementsInformation[gameWorldControllerKey] = mainGameWorldController;
	
	makeMainGameWorldData();

	ViewElementInformation mainGameHudController;
	mainGameHudController.elementPosition = Vec2(0, 0);
	mainGameHudController.elementZOrder = kHudControllerZOrder;
	_elementsInformation[gameHudControllerKey] = mainGameHudController;

	makeMainGameHudsData();

	ViewElementInformation mainGamePausePopUp;
	mainGamePausePopUp.elementPosition = Vec2(0, 0);
	mainGamePausePopUp.elementActionFinalPosition = getScreenCenter();
	mainGamePausePopUp.elementZOrder = kMainGamePausePopUpZOrder;
	_elementsInformation[mainGamePausePopUpKey] = mainGamePausePopUp;

	makeMainGamePausePopUpData();
}

void GameViewInformationFactory::makeMainGameWorldData()
{
	ViewElementInformation mainGameBackground;
	mainGameBackground.elementPosition = getScreenCenter();
	mainGameBackground.elementZOrder = kMainGameBackgroundZOrder;
	_elementsInformation[mainGameBackgroundControllerKey] = mainGameBackground;

	int gameBoardOffsetX = 12;
	int gameBoardOffsetY = 12;

	ViewElementInformation mainGameBoard;
	mainGameBoard.elementPosition = Vec2(gameBoardOffsetX, gameBoardOffsetY);
	mainGameBoard.elementOffset = Vec2(gameBoardOffsetX * 2, gameBoardOffsetY * 2);
	mainGameBoard.elementZOrder = kMainGameBoardZOrder;
	_elementsInformation[mainGameBoardControllerKey] = mainGameBoard;

	ViewElementInformation mainGameAnimation;
	mainGameAnimation.elementPosition = Vec2(gameBoardOffsetX, gameBoardOffsetY);
	mainGameAnimation.elementZOrder = kMainGameAnimationZOrder;
	_elementsInformation[mainGameAnimationControllerKey] = mainGameAnimation;

}

void GameViewInformationFactory::makeMainGameHudsData()
{
	ViewElementInformation mainGameHudsBackground;
	mainGameHudsBackground.elementPosition =  Vec2(290, getScreenCenterY());
	mainGameHudsBackground.elementZOrder = kMainGameHudsBackgroundZOrder;
	_elementsInformation[gameHudBackgroundKey] = mainGameHudsBackground;

	ViewElementInformation mainGamePlayerActionController;
	mainGamePlayerActionController.elementPosition =  Vec2(280, 40);
	mainGamePlayerActionController.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[playerActionControllerKey] = mainGamePlayerActionController;

	makeMainGamePlayerControllersData();

	ViewElementInformation mainGamePlayerScoreController;
	mainGamePlayerScoreController.elementPosition =  Vec2(280, 440);
	mainGamePlayerScoreController.elementZOrder = kMainGamePlayerScoreControllerZOrder;
	_elementsInformation[playerScoreControllerKey] = mainGamePlayerScoreController;

	makeMainGamePlayerScoreControllersData();

	ViewElementInformation victoryConditionHudController;
	victoryConditionHudController.elementPosition =  Vec2(280, 350);
	victoryConditionHudController.elementZOrder = kMainGamePlayerVictoryConditionZOrder;
	_elementsInformation[victoryConditionHudControllerKey] = victoryConditionHudController;

	makeMainGameVictoryConditionData();

	ViewElementInformation mainGamePlayerSpellsController;
	mainGamePlayerSpellsController.elementPosition =  Vec2(280, 280);
	mainGamePlayerSpellsController.elementOffset = Vec2(0, 60);
	mainGamePlayerSpellsController.elementZOrder = kMainGamePlayerSpellsControllerZOrder;
	_elementsInformation[playerSpellsControllerKey] = mainGamePlayerSpellsController;

	makeMainGameSpellsIconsData();
	makeRemoveCurrentDetailSpellData();

	ViewElementInformation meteorForFirestormSpell;
	meteorForFirestormSpell.elementPosition =  Vec2(0, 600);
	meteorForFirestormSpell.elementZOrder = 0;
	_elementsInformation[meteorForFirestormSpellKey] = meteorForFirestormSpell;

	ViewElementInformation pauseGameViewController;
	pauseGameViewController.elementPosition = Vec2(305, 65);
	pauseGameViewController.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[pauseGameViewControllerKey] = pauseGameViewController;
	
}

void GameViewInformationFactory::makeMainGamePlayerControllersData()
{
	int controllerOffset = 25;

	ViewElementInformation rotateDetailControl;
	rotateDetailControl.elementImage = getImageNameForKey(rotateDetailControlKey);
	rotateDetailControl.elementPosition = Vec2(0, controllerOffset);
	rotateDetailControl.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[rotateDetailControlKey] = rotateDetailControl;

	ViewElementInformation accelerateDetailControl;
	accelerateDetailControl.elementImage = getImageNameForKey(accelerateDetailControlKey);
	accelerateDetailControl.elementPosition = Vec2(0, 0);
	accelerateDetailControl.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[accelerateDetailControlKey] = accelerateDetailControl;

	ViewElementInformation moveDetailLeftControl;
	moveDetailLeftControl.elementImage = getImageNameForKey(moveDetailLeftControlKey);
	moveDetailLeftControl.elementPosition = Vec2(-controllerOffset, 0);
	moveDetailLeftControl.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[moveDetailLeftControlKey] = moveDetailLeftControl;

	ViewElementInformation moveDetailRightControl;
	moveDetailRightControl.elementImage = getImageNameForKey(moveDetailRightControlKey);
	moveDetailRightControl.elementPosition = Vec2(controllerOffset, 0);
	moveDetailRightControl.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[moveDetailRightControlKey] = moveDetailRightControl;
}

void GameViewInformationFactory::makeMainGamePlayerScoreControllersData()
{
	ViewElementInformation scoreControllerBackground;
	scoreControllerBackground.elementPosition =  Vec2(0, 0);
	scoreControllerBackground.elementZOrder = kMainGamePlayerScoreBackgroundZOrder;
	_elementsInformation[playerScoreControllerBackgroundKey] = scoreControllerBackground;

	ViewElementInformation scoreControllerCountLabel;
	scoreControllerCountLabel.elementPosition =  Vec2(0, 0);
	scoreControllerCountLabel.elementZOrder = kMainGamePlayerScoreCountZOrder;
	_elementsInformation[playerScoreControllerCountKey] = scoreControllerCountLabel;
}

void GameViewInformationFactory::makeMainGameVictoryConditionData()
{
	int padLength = 100;

	ViewElementInformation victoryConditionHudImage;
	victoryConditionHudImage.elementPosition =  Vec2(-(padLength/2), 30);
	victoryConditionHudImage.elementOffset = Vec2(padLength, 0);
	victoryConditionHudImage.elementZOrder = kVictoryConditionHudImageZOrder;
	_elementsInformation[victoryConditionHudImageKey] = victoryConditionHudImage;

	ViewElementInformation victoryConditionState;
	victoryConditionState.elementPosition =  Vec2(-(padLength/2), 0);
	victoryConditionState.elementOffset = Vec2(padLength, 0);
	victoryConditionState.elementZOrder = kVictoryConditionStateZOrder;
	_elementsInformation[victoryConditionHudStateKey] = victoryConditionState;
}

void GameViewInformationFactory::makeMainGameSpellsIconsData()
{
	ViewElementInformation spellIcon;
	spellIcon.elementPosition =  Vec2(0, 30);
	spellIcon.elementZOrder = kSpellIconImageZOrder;
	_elementsInformation[playerSpellImageKey] = spellIcon;

	ViewElementInformation spellCost;
	spellCost.elementPosition =  Vec2(0, 0);
	spellCost.elementZOrder = kSpellCostLabelZOrder;
	_elementsInformation[playerSpellCostLabelKey] = spellCost;
}

void GameViewInformationFactory::makeRemoveCurrentDetailSpellData()
{
	ViewElementInformation rocketForRemoveDetail;
	rocketForRemoveDetail.elementPosition =  Vec2(280, 280);
	rocketForRemoveDetail.elementZOrder = kRocketForRemoveDetailZOrder;
	_elementsInformation[rocketForRemoveCurrentDetailSpellKey] = rocketForRemoveDetail;

	ViewElementInformation detailForRemoveDetail;
	detailForRemoveDetail.elementZOrder = kDetailForRemoveCurrentDetailZOrder;
	_elementsInformation[detailForRemoveCurrentDetailSpellKey] = detailForRemoveDetail;

	ViewElementInformation explosionsForRemoveDetail;
	explosionsForRemoveDetail.elementPosition =  Vec2(0, 0);
	explosionsForRemoveDetail.elementZOrder = kExplosionsForRemoveDetailZOrder;
	_elementsInformation[explosionsForRemoveCurrentDetailSpellKey] = explosionsForRemoveDetail;
}

void GameViewInformationFactory::makeMainGamePausePopUpData()
{
	ViewElementInformation mainGamePauseRegulateSoundPopUpPad;
	mainGamePauseRegulateSoundPopUpPad.elementImage = getImageNameForKey(startGameRegulateSoundPadKey);
	mainGamePauseRegulateSoundPopUpPad.elementPosition = Vec2(getScreenCenterX(), 650);
	mainGamePauseRegulateSoundPopUpPad.elementActionFinalPosition = getScreenCenter();
	mainGamePauseRegulateSoundPopUpPad.elementZOrder = kMainGamePausePopUpPadZOrder;
	_elementsInformation[mainGamePausePadKey] = mainGamePauseRegulateSoundPopUpPad;
	
	ViewElementInformation mainGamePauseRegulateSoundSlider;
	mainGamePauseRegulateSoundSlider.elementImage = getImageNameForKey(startGameRegulateSoundSliderKey);
	mainGamePauseRegulateSoundSlider.elementPosition = Vec2(90, 160);
	mainGamePauseRegulateSoundSlider.elementZOrder = kMainGamePauseRegulateSoundSliderZOrder;
	_elementsInformation[mainGamePauseRegulateSoundSliderKey] = mainGamePauseRegulateSoundSlider;
	
	ViewElementInformation mainGamePauseRegulateSoundEffectsSlider;
	mainGamePauseRegulateSoundEffectsSlider.elementImage = getImageNameForKey(startGameRegulateSoundEffectsSliderKey);
	mainGamePauseRegulateSoundEffectsSlider.elementPosition = Vec2(90, 120);
	mainGamePauseRegulateSoundEffectsSlider.elementZOrder = kMainGamePauseRegulateSoundEffectsSliderZOrder;
	_elementsInformation[mainGamePauseRegulateSoundEffectsSliderKey] = mainGamePauseRegulateSoundEffectsSlider;
	
	ViewElementInformation mainGamePauseRegulateSoundCloseButton;
	mainGamePauseRegulateSoundCloseButton.elementImage = getImageNameForKey(startGameRegulateSoundCloseButtonKey);
	mainGamePauseRegulateSoundCloseButton.elementPosition = Vec2(150, 60);
	mainGamePauseRegulateSoundCloseButton.elementZOrder = kMainGamePausePopUpCloseButtonZOrder;
	_elementsInformation[mainGamePauseCloseButtonKey] = mainGamePauseRegulateSoundCloseButton;

	ViewElementInformation mainGamePauseGoToSelectLevelButton;
	mainGamePauseGoToSelectLevelButton.elementImage = getImageNameForKey(mainGamePauseGoToSelectLevelButtonKey);
	mainGamePauseGoToSelectLevelButton.elementPosition = Vec2(150, 20);
	mainGamePauseGoToSelectLevelButton.elementZOrder = kMainGamePauseGoToSelectLevelButtonZOrder;
	_elementsInformation[mainGamePauseGoToSelectLevelButtonKey] = mainGamePauseGoToSelectLevelButton;
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


