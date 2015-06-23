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
	_elementsInformation =  map <string , ViewElementInformation>();
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
	makeFinalScreenData();
}

void GameViewInformationFactory::makeLoadingScreenData()
{
	ViewElementInformation loadingScreenBackground;
	loadingScreenBackground.elementImage = getImageNameForKey(loadingGameBackgroundKey);
	loadingScreenBackground.elementPosition = getScreenCenter();
	loadingScreenBackground.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[loadingGameBackgroundKey] = loadingScreenBackground;

	ViewElementInformation loadingGameWave;
	loadingGameWave.elementImage = getImageNameForKey(loadingGameWaveKey);
	loadingGameWave.elementPosition = Vec2(0, 60) + getScreenCenter();
	loadingGameWave.elementZOrder = kLoadingGameWaveZOrder;
	_elementsInformation[loadingGameWaveKey] = loadingGameWave;
	
	ViewElementInformation loadingBeaver;
	loadingBeaver.elementImage = getImageNameForKey(loadingGameBeaverKey);
	loadingBeaver.elementPosition = getScreenCenter() - Vec2(0, 130);
	loadingBeaver.elementZOrder = kLoadingBeaverZOrder;
	_elementsInformation[loadingGameBeaverKey] = loadingBeaver;

	ViewElementInformation loadingGameName;
	loadingGameName.elementImage = getImageNameForKey(loadingGameNameKey);
	loadingGameName.elementPosition = Vec2(175, 610);
	loadingGameName.elementZOrder = kLoadingGameNameZOrder;
	_elementsInformation[loadingGameNameKey] = loadingGameName;
	
	ViewElementInformation loadingClock;
	loadingClock.elementImage = getImageNameForKey(loadingGameClockKey);
	loadingClock.elementPosition = Vec2(315, 178);
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

	ViewElementInformation startGameFishes;
	startGameFishes.elementPosition = Vec2(0, 0);
	startGameFishes.elementZOrder = kStartGameFishesZOrder;
	_elementsInformation[startGameFishesKey] = startGameFishes;

	makeStartGameFishesData();

	ViewElementInformation startGameMenu;
	startGameMenu.elementImage = getImageNameForKey(startGameMenuKey);
	startGameMenu.elementPosition = getScreenCenter() - Vec2(0, 800);
	startGameMenu.elementActionFinalPosition = getScreenCenter() - Vec2(0, 60);
	startGameMenu.elementZOrder = kLoadingBackgroundZOrder;
	_elementsInformation[startGameMenuKey] = startGameMenu;

	ViewElementInformation startGameMenuButtonText;
	startGameMenuButtonText.elementPosition = Vec2(12, 5);
	startGameMenuButtonText.elementZOrder = 0;
	_elementsInformation[startGameMenuButtonTextKey] = startGameMenuButtonText;

	makeStartGameMenuItemsData();

	ViewElementInformation startGameBeaver;
	startGameBeaver.elementImage = getImageNameForKey(startGameBeaverKey);
	startGameBeaver.elementPosition = Vec2(1680, 220);
	startGameBeaver.elementActionFinalPosition = Vec2(890, 440);
	startGameBeaver.elementOffset = Vec2(0, 250);
	startGameBeaver.elementZOrder = kStartGameBeaverZOrder;
	_elementsInformation[startGameBeaverKey] = startGameBeaver;

	ViewElementInformation startGameRegulateSoundPopUp;
	startGameRegulateSoundPopUp.elementPosition = Vec2(0, 0);
	startGameRegulateSoundPopUp.elementActionFinalPosition = getScreenCenter();
	startGameRegulateSoundPopUp.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameRegulateSoundPopUpKey] = startGameRegulateSoundPopUp;

	makeStartGameRegulateSoundPopUpData();

}

void GameViewInformationFactory::makeStartGameFishesData()
{
	ViewElementInformation startGameFish1;
	startGameFish1.elementImage = getImageNameForKey(startGameFish1Key);
	startGameFish1.elementPosition = Vec2(1680, 150);
	startGameFish1.elementActionFinalPosition = Vec2(-110, 150);
	startGameFish1.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameFish1Key] = startGameFish1;

	ViewElementInformation startGameFish2;
	startGameFish2.elementImage = getImageNameForKey(startGameFish2Key);
	startGameFish2.elementPosition = Vec2(-110, 50);
	startGameFish2.elementActionFinalPosition = Vec2(1680, 50);
	startGameFish2.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameFish2Key] = startGameFish2;

	ViewElementInformation startGameFish3;
	startGameFish3.elementImage = getImageNameForKey(startGameFish3Key);
	startGameFish3.elementPosition = Vec2(-110, 100);
	startGameFish3.elementActionFinalPosition = Vec2(1680, 100);
	startGameFish3.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[startGameFish3Key] = startGameFish3;

}

void GameViewInformationFactory::makeStartGameMenuItemsData()
{

	ViewElementInformation createNewGameButton;
	createNewGameButton.elementPosition = Vec2(0, 310);
	createNewGameButton.elementOffset = Vec2(10, 0);
	createNewGameButton.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[createNewGameButtonKey] = createNewGameButton;

	ViewElementInformation selectGameLevelButton;
	selectGameLevelButton.elementPosition = Vec2(0, 220);
	selectGameLevelButton.elementOffset = Vec2(10, 0);
	selectGameLevelButton.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[selectGameLevelButtonKey] = selectGameLevelButton;

	ViewElementInformation goToGameRecordsButton;
	goToGameRecordsButton.elementPosition = Vec2(0, 130);
	goToGameRecordsButton.elementOffset = Vec2(10, 0);
	goToGameRecordsButton.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[goToGameRecordsButtonKey] = goToGameRecordsButton;

	ViewElementInformation getSoundRegulatorsButton;
	getSoundRegulatorsButton.elementPosition = Vec2(-45, 40);
	getSoundRegulatorsButton.elementOffset = Vec2(10, 0);
	getSoundRegulatorsButton.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[getSoundRegulatorsButtonKey] = getSoundRegulatorsButton;

	ViewElementInformation goToDevelopersButton;
	goToDevelopersButton.elementPosition = Vec2(-45, -40);
	goToDevelopersButton.elementOffset = Vec2(10, 0);
	goToDevelopersButton.elementZOrder = kStartGameBackgroundZOrder;
	_elementsInformation[goToDevelopersButtonKey] = goToDevelopersButton;

}

void GameViewInformationFactory::makeStartGameRegulateSoundPopUpData()
{
	ViewElementInformation startGameRegulateSoundBackground;
	startGameRegulateSoundBackground.elementImage = getImageNameForKey(startGameRegulateSoundBackgroundKey);
	startGameRegulateSoundBackground.elementPosition = getScreenCenter();
	startGameRegulateSoundBackground.elementZOrder = kStartGameRegulateSoundPopUpPadZOrder;
	_elementsInformation[startGameRegulateSoundBackgroundKey] = startGameRegulateSoundBackground;

	ViewElementInformation startGameRegulateSoundPopUpPad;
	startGameRegulateSoundPopUpPad.elementImage = getImageNameForKey(startGameRegulateSoundPadKey);
	startGameRegulateSoundPopUpPad.elementPosition = getScreenCenter() + Vec2(0, 150);
	startGameRegulateSoundPopUpPad.elementZOrder = kStartGameRegulateSoundPopUpPadZOrder;
	_elementsInformation[startGameRegulateSoundPadKey] = startGameRegulateSoundPopUpPad;

	ViewElementInformation startGameRegulateSoundPad;
	startGameRegulateSoundPad.elementImage = getImageNameForKey(startGameRegulateSoundPlaceKey);
	startGameRegulateSoundPad.elementPosition = Vec2(0, 0);
	startGameRegulateSoundPad.elementZOrder = 0;
	_elementsInformation[startGameRegulateSoundPlaceKey] = startGameRegulateSoundPad;

	ViewElementInformation startGameRegulateSoundSlider;
	startGameRegulateSoundSlider.elementPosition = Vec2(110, 460);
	startGameRegulateSoundSlider.elementZOrder = kStartGameRegulateSoundSliderZOrder;
	_elementsInformation[startGameRegulateSoundSliderKey] = startGameRegulateSoundSlider;

	ViewElementInformation startGameRegulateBackgroundSoundIcon;
	startGameRegulateBackgroundSoundIcon.elementImage = getImageNameForKey(startGameRegulateBackgroundSoundIconKey);
	startGameRegulateBackgroundSoundIcon.elementPosition = Vec2(-215, 0);
	startGameRegulateBackgroundSoundIcon.elementZOrder = 0;
	_elementsInformation[startGameRegulateBackgroundSoundIconKey] = startGameRegulateBackgroundSoundIcon;

	ViewElementInformation startGameRegulateSoundEffectsSlider;
	startGameRegulateSoundEffectsSlider.elementImage = getImageNameForKey(startGameRegulateSoundEffectsSliderKey);
	startGameRegulateSoundEffectsSlider.elementPosition = Vec2(110, 330);
	startGameRegulateSoundEffectsSlider.elementZOrder = kStartGameRegulateSoundEffectsSliderZOrder;
	_elementsInformation[startGameRegulateSoundEffectsSliderKey] = startGameRegulateSoundEffectsSlider;

	ViewElementInformation startGameRegulateSoundEffectsIcon;
	startGameRegulateSoundEffectsIcon.elementImage = getImageNameForKey(startGameRegulateSoundEffectsIconKey);
	startGameRegulateSoundEffectsIcon.elementPosition = Vec2(-215, 0);
	startGameRegulateSoundEffectsIcon.elementZOrder = 0;
	_elementsInformation[startGameRegulateSoundEffectsIconKey] = startGameRegulateSoundEffectsIcon;

	ViewElementInformation startGameRegulateSoundCloseButton;
	startGameRegulateSoundCloseButton.elementImage = startGameRegulateSoundCloseButtonKey;
	startGameRegulateSoundCloseButton.elementPosition = Vec2(115, 10);
	startGameRegulateSoundCloseButton.elementZOrder = kStartGameRegulateSoundPopUpCloseButtonZOrder;
	_elementsInformation[startGameRegulateSoundCloseButtonKey] = startGameRegulateSoundCloseButton;

	ViewElementInformation closeButtonText;
	closeButtonText.elementPosition = Vec2(0, 0);
	closeButtonText.elementZOrder = 0;
	_elementsInformation[closeButtonTextKey] = closeButtonText;

}

void GameViewInformationFactory::makeSelectGameLevelScreenData()
{

	ViewElementInformation selectGameLevelBackground;
	selectGameLevelBackground.elementImage = getImageNameForKey(selectLevelBackgroundKey);
	selectGameLevelBackground.elementPosition = getScreenCenter();
	selectGameLevelBackground.elementZOrder = 0;
	_elementsInformation[selectLevelBackgroundKey] = selectGameLevelBackground;

	makeSelectGameLevelBackgroundData();

	ViewElementInformation selectGameLevelBeaverTalk;
	selectGameLevelBeaverTalk.elementImage = getImageNameForKey(selectLevelBeaverTalkKey);
	selectGameLevelBeaverTalk.elementPosition = Vec2(1750, 100);
	selectGameLevelBeaverTalk.elementActionFinalPosition = Vec2(1245, 100);
	selectGameLevelBeaverTalk.elementZOrder = kSelectLevelSceneBeaverTalkZOrder;
	_elementsInformation[selectLevelBeaverTalkKey] = selectGameLevelBeaverTalk;

	ViewElementInformation selectLevelBeaverBlobTalk;
	selectLevelBeaverBlobTalk.elementImage = getImageNameForKey(selectLevelBeaverBlobTalkKey);
	selectLevelBeaverBlobTalk.elementPosition = Vec2(-200, 80);
	selectLevelBeaverBlobTalk.elementZOrder = 0;
	_elementsInformation[selectLevelBeaverBlobTalkKey] = selectLevelBeaverBlobTalk;

	ViewElementInformation selectGameLevelBeaverTalkText;
	selectGameLevelBeaverTalkText.elementPosition = Vec2(-200, 30);
	selectGameLevelBeaverTalkText.elementZOrder = 0;
	_elementsInformation[selectLevelBeaverTalkTextKey] = selectGameLevelBeaverTalkText;

	ViewElementInformation selectGameLevelMenu;
	selectGameLevelMenu.elementImage = getImageNameForKey(selectLevelMenuKey);
	selectGameLevelMenu.elementPosition = Vec2(0, 0);
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
	selectLevelSceneBackButton.elementImage = selectLevelSceneBackButtonKey;
	selectLevelSceneBackButton.elementPosition = Vec2(180, 90);
	selectLevelSceneBackButton.elementZOrder = kSelectLevelSceneBackButtonZOrder;
	_elementsInformation[selectLevelSceneBackButtonKey] = selectLevelSceneBackButton;

	ViewElementInformation selectLevelBeaverOnRaft;
	selectLevelBeaverOnRaft.elementImage = getImageNameForKey(selectLevelBeaverOnRaftKey);
	selectLevelBeaverOnRaft.elementPosition = Vec2(0, 0);
	selectLevelBeaverOnRaft.elementZOrder = 0;
	_elementsInformation[selectLevelBeaverOnRaftKey] = selectLevelBeaverOnRaft;

}

void GameViewInformationFactory::makeSelectGameLevelBackgroundData()
{
	ViewElementInformation leftGround;
	leftGround.elementImage = getImageNameForKey(selectLevelBackgroundLeftKey);
	leftGround.elementPosition = Vec2(460, 460);
	leftGround.elementZOrder = 0;
	_elementsInformation[selectLevelBackgroundLeftKey] = leftGround;

	ViewElementInformation rightGround;
	rightGround.elementImage = getImageNameForKey(selectLevelBackgroundRightKey);
	rightGround.elementPosition = Vec2(1140, 610);
	rightGround.elementZOrder = 0;
	_elementsInformation[selectLevelBackgroundRightKey] = rightGround;
}

void GameViewInformationFactory::makeSelectGameLevelMenuData()
{
	ViewElementInformation gameLevel1;
	gameLevel1.elementPosition = Vec2(500, 120);
	gameLevel1.elementOffset = Vec2(60, 20);
	gameLevel1.elementActionFinalPosition = Vec2(1150, 280);
	_elementsInformation[gameLevel1Key] = gameLevel1;

	ViewElementInformation gameLevel2;
	gameLevel2.elementPosition = Vec2(425, 240);
	gameLevel2.elementOffset = Vec2(60, 20);
	gameLevel2.elementActionFinalPosition = Vec2(850, 270);
	_elementsInformation[gameLevel2Key] = gameLevel2;

	ViewElementInformation gameLevel3;
	gameLevel3.elementPosition = Vec2(280, 340);
	gameLevel3.elementOffset = Vec2(80, 10);
	gameLevel3.elementActionFinalPosition = Vec2(780, 290);
	_elementsInformation[gameLevel3Key] = gameLevel3;

	ViewElementInformation gameLevel4;
	gameLevel4.elementPosition = Vec2(405, 440);
	gameLevel4.elementOffset = Vec2(80, 20);
	gameLevel4.elementActionFinalPosition = Vec2(630, 340);
	_elementsInformation[gameLevel4Key] = gameLevel4;

	ViewElementInformation gameLevel5;
	gameLevel5.elementPosition = Vec2(950, 380);
	gameLevel5.elementOffset = Vec2(60, 20);
	gameLevel5.elementActionFinalPosition = Vec2(670, 440);
	_elementsInformation[gameLevel5Key] = gameLevel5;

	ViewElementInformation gameLevel6;
	gameLevel6.elementPosition = Vec2(1150, 450);
	gameLevel6.elementOffset = Vec2(80, 20);
	gameLevel6.elementActionFinalPosition = Vec2(650, 500);
	_elementsInformation[gameLevel6Key] = gameLevel6;

	ViewElementInformation gameLevel7;
	gameLevel7.elementPosition = Vec2(900, 550);
	gameLevel7.elementOffset = Vec2(60, 20);
	gameLevel7.elementActionFinalPosition = Vec2(700, 550);
	_elementsInformation[gameLevel7Key] = gameLevel7;

	ViewElementInformation gameLevel8;
	gameLevel8.elementPosition = Vec2(1050, 650);
	gameLevel8.elementOffset = Vec2(-80, -10);
	gameLevel8.elementActionFinalPosition = Vec2(700, 550);
	_elementsInformation[gameLevel8Key] = gameLevel8;

	ViewElementInformation gameLevel9;
	gameLevel9.elementPosition = Vec2(800, 665);
	gameLevel9.elementOffset = Vec2(80, 30);
	gameLevel9.elementActionFinalPosition = Vec2(640, 620);
	_elementsInformation[gameLevel9Key] = gameLevel9;

	ViewElementInformation gameLevel10;
	gameLevel10.elementPosition = Vec2(450, 690);
	gameLevel10.elementOffset = Vec2(60, 20);
	gameLevel10.elementActionFinalPosition = Vec2(640, 620);
	_elementsInformation[gameLevel10Key] = gameLevel10;

}

void GameViewInformationFactory::makeSelectGameLevelPlayerStatusData()
{
	ViewElementInformation selectGameLevelPlayerStatusPad;
	selectGameLevelPlayerStatusPad.elementImage = getImageNameForKey(selectLevelScenePlayerStatusPadKey);
	selectGameLevelPlayerStatusPad.elementPosition = Vec2(150, 880);
	selectGameLevelPlayerStatusPad.elementActionFinalPosition = Vec2(150, 640);
	selectGameLevelPlayerStatusPad.elementZOrder = kSelectLevelPlayerStatusPadZOrder;
	_elementsInformation[selectLevelScenePlayerStatusPadKey] = selectGameLevelPlayerStatusPad;

	ViewElementInformation selectLevelScenePlayerStatusName;
	selectLevelScenePlayerStatusName.elementPosition = Vec2(105, 105);
	selectLevelScenePlayerStatusName.elementZOrder = kSelectLevelPlayerStatusNameZOrder;
	_elementsInformation[selectLevelScenePlayerStatusNameKey] = selectLevelScenePlayerStatusName;

	ViewElementInformation selectLevelScenePlayerStatusScore;
	selectLevelScenePlayerStatusScore.elementPosition = Vec2(105, 75);
	selectLevelScenePlayerStatusScore.elementZOrder = kSelectLevelPlayerStatusScoreZOrder;
	_elementsInformation[selectLevelScenePlayerStatusScoreKey] = selectLevelScenePlayerStatusScore;

}

void GameViewInformationFactory::makeSelectGameLevelPlayerCreatorControllerData()
{
	ViewElementInformation playerCreatorBackground;
	playerCreatorBackground.elementImage = getImageNameForKey(playerCreatorControllerBackgroundKey);
	playerCreatorBackground.elementPosition = getScreenCenter();
	playerCreatorBackground.elementZOrder = kPlayerCreatorBackgroundZOrder;
	_elementsInformation[playerCreatorControllerBackgroundKey] = playerCreatorBackground;

	ViewElementInformation playerCreatorPad;
	playerCreatorPad.elementImage = getImageNameForKey(playerCreatorControllerPadKey);
	playerCreatorPad.elementPosition = Vec2(0, 130) + getScreenCenter();
	playerCreatorPad.elementZOrder = kPlayerCreatorPadZOrder;
	_elementsInformation[playerCreatorControllerPadKey] = playerCreatorPad;

	ViewElementInformation playerCreatorText;
	playerCreatorText.elementPosition = Vec2(95, 400);
	playerCreatorText.elementZOrder = kPlayerCreatorTextZOrder;
	_elementsInformation[playerCreatorControllerTextKey] = playerCreatorText;

	ViewElementInformation playerCreatorInput;
	playerCreatorInput.elementPosition = Vec2(95, 400);
	playerCreatorInput.elementZOrder = kPlayerCreatorInputZOrder;
	_elementsInformation[playerCreatorControllerInputKey] = playerCreatorInput;

	ViewElementInformation playerCreatorControllerBackButton;
	playerCreatorControllerBackButton.elementImage = playerCreatorControllerBackButtonKey;
	playerCreatorControllerBackButton.elementPosition = Vec2(113, 10);
	playerCreatorControllerBackButton.elementZOrder = kPlayerCreatorInputZOrder;
	_elementsInformation[playerCreatorControllerBackButtonKey] = playerCreatorControllerBackButton;
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

	ViewElementInformation gameTutorialController;
	gameTutorialController.elementPosition = Vec2(0, 0);
	gameTutorialController.elementZOrder = kGameTutorialControllerZOrder;
	_elementsInformation[gameTutorialControllerKey] = gameTutorialController;

	makeMainGameTutorialData();

	ViewElementInformation mainGamePausePopUp;
	mainGamePausePopUp.elementPosition = Vec2(0, 0);
	mainGamePausePopUp.elementActionFinalPosition = getScreenCenter();
	mainGamePausePopUp.elementZOrder = kMainGamePausePopUpZOrder;
	_elementsInformation[mainGamePausePopUpKey] = mainGamePausePopUp;

	makeMainGamePausePopUpData();

	ViewElementInformation mainGameEndPopUp;
	mainGameEndPopUp.elementPosition = Vec2(0, 0);
	mainGameEndPopUp.elementZOrder = kMainGameEndPopUpZOrder;
	_elementsInformation[mainGameEndPopUpKey] = mainGameEndPopUp;

	makeMainGameEndPopUpData();

}

void GameViewInformationFactory::makeMainGameWorldData()
{
	ViewElementInformation mainGameBackground;
	mainGameBackground.elementImage = getImageNameForKey(mainGameBackgroundControllerKey);
	mainGameBackground.elementPosition = getScreenCenter();
	mainGameBackground.elementZOrder = kMainGameBackgroundZOrder;
	_elementsInformation[mainGameBackgroundControllerKey] = mainGameBackground;

	ViewElementInformation mainGameBorder;
	mainGameBorder.elementImage = getImageNameForKey(mainGameBorderKey);
	mainGameBorder.elementPosition = Vec2(8, 0);
	mainGameBorder.elementZOrder = kMainGameBorderZOrder;
	_elementsInformation[mainGameBorderKey] = mainGameBorder;

	ViewElementInformation mainGameBackgroundPad;
	mainGameBackgroundPad.elementImage = getImageNameForKey(mainGameBackgroundPadKey);
	mainGameBackgroundPad.elementPosition = Vec2(-43, 0);
	mainGameBackgroundPad.elementZOrder = kMainGamePadZOrder;
	_elementsInformation[mainGameBackgroundPadKey] = mainGameBackgroundPad;

	int gameTetraminoOffsetX = 19;
	int gameTetraminoOffsetY = 19;

	ViewElementInformation mainGameBoard;
	mainGameBoard.elementPosition = Vec2(469, gameTetraminoOffsetY);
	mainGameBoard.elementOffset = Vec2(gameTetraminoOffsetX * 2, gameTetraminoOffsetY * 2);
	mainGameBoard.elementZOrder = kMainGameBoardZOrder;
	_elementsInformation[mainGameBoardControllerKey] = mainGameBoard;

	ViewElementInformation tetraminoLivesCountView;
	tetraminoLivesCountView.elementPosition = Vec2(-4, -4);
	tetraminoLivesCountView.elementZOrder = 0;
	_elementsInformation[tetraminoLivesCountViewKey] = tetraminoLivesCountView;

	ViewElementInformation mainGameAnimation;
	mainGameAnimation.elementPosition = mainGameBoard.elementPosition;
	mainGameAnimation.elementZOrder = kMainGameAnimationZOrder;
	_elementsInformation[mainGameAnimationControllerKey] = mainGameAnimation;

}

void GameViewInformationFactory::makeMainGameHudsData()
{
	ViewElementInformation mainGameHudsBackground;
	mainGameHudsBackground.elementImage = getImageNameForKey(gameHudBackgroundKey);
	mainGameHudsBackground.elementPosition = getScreenCenter() + Vec2(200, 0);
	mainGameHudsBackground.elementZOrder = kMainGameHudsBackgroundZOrder;
	_elementsInformation[gameHudBackgroundKey] = mainGameHudsBackground;

	int hudElementXPosition = getScreenCenterX() + 200;

	ViewElementInformation mainGamePlayerActionController;
	mainGamePlayerActionController.elementPosition = getScreenCenter() + Vec2(580, -80);
	mainGamePlayerActionController.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[playerActionControllerKey] = mainGamePlayerActionController;

	makeMainGamePlayerControllersData();

	ViewElementInformation mainGamePlayerScoreController;
	mainGamePlayerScoreController.elementPosition =  Vec2(hudElementXPosition, 700);
	mainGamePlayerScoreController.elementZOrder = kMainGamePlayerScoreControllerZOrder;
	_elementsInformation[playerScoreControllerKey] = mainGamePlayerScoreController;

	makeMainGamePlayerScoreControllersData();

	ViewElementInformation victoryConditionHudController;
	victoryConditionHudController.elementPosition =  Vec2(hudElementXPosition, 600);
	victoryConditionHudController.elementOffset = Vec2(0, 16);
	victoryConditionHudController.elementZOrder = kMainGamePlayerVictoryConditionZOrder;
	_elementsInformation[victoryConditionHudControllerKey] = victoryConditionHudController;

	makeMainGameVictoryConditionData();

	ViewElementInformation mainGamePlayerSpellsController;
	mainGamePlayerSpellsController.elementPosition = getScreenCenter() + Vec2(580, 280);
	mainGamePlayerSpellsController.elementOffset = Vec2(0, 80);
	mainGamePlayerSpellsController.elementZOrder = kMainGamePlayerSpellsControllerZOrder;
	_elementsInformation[playerSpellsControllerKey] = mainGamePlayerSpellsController;

	makeMainGameSpellsIconsData();
	makeRemoveCurrentDetailSpellData();

	ViewElementInformation meteorForFirestormSpell;
	meteorForFirestormSpell.elementPosition =  Vec2(0, 800);
	meteorForFirestormSpell.elementZOrder = 0;
	_elementsInformation[meteorForFirestormSpellKey] = meteorForFirestormSpell;

	ViewElementInformation pauseGameViewController;
	pauseGameViewController.elementImage = getImageNameForKey(pauseGameViewControllerKey);
	pauseGameViewController.elementPosition = getScreenCenter() + Vec2(580, -180);
	pauseGameViewController.elementZOrder = kMainGamePlayerActionControllerZOrder;
	_elementsInformation[pauseGameViewControllerKey] = pauseGameViewController;
	
}

void GameViewInformationFactory::makeMainGamePlayerControllersData()
{
	int controllerOffset = 65;

	ViewElementInformation rotateDetailControl;
	rotateDetailControl.elementPosition = Vec2(0, controllerOffset);
	rotateDetailControl.elementOffset = Vec2(0, 0);
	_elementsInformation[rotateDetailControlKey] = rotateDetailControl;

	ViewElementInformation accelerateDetailControl;
	accelerateDetailControl.elementPosition = Vec2(-8, 0);
	accelerateDetailControl.elementOffset = Vec2(180, 0);
	_elementsInformation[accelerateDetailControlKey] = accelerateDetailControl;

	ViewElementInformation moveDetailLeftControl;
	moveDetailLeftControl.elementPosition = Vec2(-controllerOffset, 0);
	moveDetailLeftControl.elementOffset = Vec2(-90, 0);
	_elementsInformation[moveDetailLeftControlKey] = moveDetailLeftControl;

	ViewElementInformation moveDetailRightControl;
	moveDetailRightControl.elementPosition = Vec2(controllerOffset, 0);
	moveDetailRightControl.elementOffset = Vec2(90, 0);
	_elementsInformation[moveDetailRightControlKey] = moveDetailRightControl;

	ViewElementInformation playerControlInactiveImage;
	playerControlInactiveImage.elementImage = getImageNameForKey(playerControlInactiveImageKey);
	_elementsInformation[playerControlInactiveImageKey] = playerControlInactiveImage;

	ViewElementInformation playerControlActiveImage;
	playerControlActiveImage.elementImage = getImageNameForKey(playerControlActiveImageKey);
	_elementsInformation[playerControlActiveImageKey] = playerControlActiveImage;

}

void GameViewInformationFactory::makeMainGamePlayerScoreControllersData()
{
	ViewElementInformation scoreControllerBackground;
	scoreControllerBackground.elementImage = getImageNameForKey(playerScoreControllerBackgroundKey);
	scoreControllerBackground.elementPosition =  Vec2(0, 0);
	scoreControllerBackground.elementZOrder = kMainGamePlayerScoreBackgroundZOrder;
	_elementsInformation[playerScoreControllerBackgroundKey] = scoreControllerBackground;

	ViewElementInformation scoreControllerCountLabel;
	scoreControllerCountLabel.elementPosition =  Vec2(55, 35);
	scoreControllerCountLabel.elementZOrder = kMainGamePlayerScoreCountZOrder;
	_elementsInformation[playerScoreControllerCountKey] = scoreControllerCountLabel;
}

void GameViewInformationFactory::makeMainGameVictoryConditionData()
{
	int padLength = 106;

	ViewElementInformation victoryConditionPad;
	victoryConditionPad.elementImage = getImageNameForKey(victoryConditionPadImageKey);
	victoryConditionPad.elementPosition =  Vec2(0, 20);
	victoryConditionPad.elementZOrder = kVictoryConditionHudImageZOrder;
	_elementsInformation[victoryConditionPadImageKey] = victoryConditionPad;

	ViewElementInformation victoryConditionHudImage;
	victoryConditionHudImage.elementPosition =  Vec2(-(padLength/2), 27);
	victoryConditionHudImage.elementOffset = Vec2(padLength, 0);
	victoryConditionHudImage.elementZOrder = kVictoryConditionHudImageZOrder;
	_elementsInformation[victoryConditionHudImageKey] = victoryConditionHudImage;

	ViewElementInformation victoryConditionState;
	victoryConditionState.elementPosition =  Vec2(-(padLength/2), -7);
	victoryConditionState.elementOffset = Vec2(padLength, 0);
	victoryConditionState.elementZOrder = kVictoryConditionStateZOrder;
	_elementsInformation[victoryConditionHudStateKey] = victoryConditionState;
}

void GameViewInformationFactory::makeMainGameSpellsIconsData()
{
	ViewElementInformation spellIcon;
	spellIcon.elementImage = getImageNameForKey(playerSpellImageKey);
	spellIcon.elementPosition =  Vec2(0, 30);
	spellIcon.elementOffset = Vec2(26, 26);
	spellIcon.elementZOrder = kSpellIconImageZOrder;
	_elementsInformation[playerSpellImageKey] = spellIcon;

	ViewElementInformation spellCost;
	spellCost.elementPosition =  Vec2(0, -10);
	spellCost.elementZOrder = kSpellCostLabelZOrder;
	_elementsInformation[playerSpellCostLabelKey] = spellCost;

	ViewElementInformation playerSpellButtonLabel;
	playerSpellButtonLabel.elementPosition =  Vec2(-35, 45);
	playerSpellButtonLabel.elementZOrder = kSpellButtonLabelZOrder;
	_elementsInformation[playerSpellButtonLabelKey] = playerSpellButtonLabel;
}

void GameViewInformationFactory::makeRemoveCurrentDetailSpellData()
{
	ViewElementInformation rocketForRemoveDetail;
	rocketForRemoveDetail.elementPosition =  Vec2(280, 800);
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

void GameViewInformationFactory::makeMainGameTutorialData()
{
	ViewElementInformation gameTutorialView;
	gameTutorialView.elementPosition = Vec2(469, -19);
	gameTutorialView.elementZOrder = kGameTutorialViewZOrder;
	_elementsInformation[gameTutorialViewKey] = gameTutorialView;

	ViewElementInformation gameTutorialBeaverTalk;
	gameTutorialBeaverTalk.elementImage = getImageNameForKey(selectLevelBeaverTalkKey);
	gameTutorialBeaverTalk.elementPosition = Vec2(1750, 100);
	gameTutorialBeaverTalk.elementActionFinalPosition = Vec2(1245, 100);
	gameTutorialBeaverTalk.elementZOrder = kGameTutorialBeaverZOrder;
	_elementsInformation[gameTutorialBeaverKey] = gameTutorialBeaverTalk;

	ViewElementInformation gameTutorialStartDetail;
	gameTutorialStartDetail.elementPosition = Vec2(76, 800);
	gameTutorialStartDetail.elementActionFinalPosition = Vec2(76, 650);
	gameTutorialStartDetail.elementOffset = Vec2(76, 75);
	gameTutorialStartDetail.elementZOrder = 0;
	_elementsInformation[gameTutorialStartDetailKey] = gameTutorialStartDetail;

	int controllerOffset = 50;
	Vec2 startControlPosition = Vec2(200, 450);

	ViewElementInformation rotateDetailControl;
	rotateDetailControl.elementPosition = Vec2(startControlPosition.x, startControlPosition.y + controllerOffset);
	rotateDetailControl.elementOffset = Vec2(0, 0);
	_elementsInformation[gameTutorialRotateDetailControlKey] = rotateDetailControl;
	
	ViewElementInformation accelerateDetailControl;
	accelerateDetailControl.elementPosition = startControlPosition;
	accelerateDetailControl.elementOffset = Vec2(180, 0);
	_elementsInformation[gameTutorialAccelerateDetailControlKey] = accelerateDetailControl;
	
	ViewElementInformation moveDetailLeftControl;
	moveDetailLeftControl.elementPosition = Vec2(startControlPosition.x - controllerOffset, startControlPosition.y);
	moveDetailLeftControl.elementOffset = Vec2(-90, 0);
	_elementsInformation[gameTutorialMoveDetailLeftControlKey] = moveDetailLeftControl;
	
	ViewElementInformation moveDetailRightControl;
	moveDetailRightControl.elementPosition = Vec2(startControlPosition.x + controllerOffset, startControlPosition.y);
	moveDetailRightControl.elementOffset = Vec2(90, 0);
	_elementsInformation[gameTutorialMoveDetailRightControlKey] = moveDetailRightControl;

	Vec2 useSpellControllPosition = Vec2(250, 500);

	ViewElementInformation useRocketSpellControl;
	useRocketSpellControl.elementImage = getImageNameForKey(gameTutorialUseRocketSpellControlKey);
	useRocketSpellControl.elementPosition = useSpellControllPosition;
	useRocketSpellControl.elementZOrder = 0;
	_elementsInformation[gameTutorialUseRocketSpellControlKey] = useRocketSpellControl;

	ViewElementInformation useRandomExplosionSpellControl;
	useRandomExplosionSpellControl.elementImage = getImageNameForKey(gameTutorialUseRandomExplosionsSpellControlKey);
	useRandomExplosionSpellControl.elementPosition = useSpellControllPosition;
	useRandomExplosionSpellControl.elementZOrder = 0;
	_elementsInformation[gameTutorialUseRandomExplosionsSpellControlKey] = useRandomExplosionSpellControl;

	ViewElementInformation useFirestormSpellControl;
	useFirestormSpellControl.elementImage = getImageNameForKey(gameTutorialUseFirestormSpellControlKey);
	useFirestormSpellControl.elementPosition = useSpellControllPosition;
	useFirestormSpellControl.elementZOrder = 0;
	_elementsInformation[gameTutorialUseFirestormSpellControlKey] = useFirestormSpellControl;

	ViewElementInformation useCohesionSpellControl;
	useCohesionSpellControl.elementImage = getImageNameForKey(gameTutorialUseCohesionSpellControlKey);
	useCohesionSpellControl.elementPosition = useSpellControllPosition;
	useCohesionSpellControl.elementZOrder = 0;
	_elementsInformation[gameTutorialUseCohesionSpellControlKey] = useCohesionSpellControl;

	ViewElementInformation useSpellRocket;
	useSpellRocket.elementPosition = Vec2(200, 850);
	useSpellRocket.elementActionFinalPosition = Vec2(76, 600);
	useSpellRocket.elementZOrder = 0;
	_elementsInformation[gameTutorialUseSpellRocketKey] = useSpellRocket;

	ViewElementInformation playerScorePad;
	playerScorePad.elementImage = getImageNameForKey(playerScoreControllerBackgroundKey);
	playerScorePad.elementPosition = Vec2(100, 500);
	playerScorePad.elementZOrder = 0;
	_elementsInformation[gameTutorialPlayerScorePadKey] = playerScorePad;

	ViewElementInformation conditionPad;
	conditionPad.elementPosition = Vec2(200, 450);
	conditionPad.elementZOrder = 0;
	_elementsInformation[gameTutorialVictoryConditionPadKey] = conditionPad;

	ViewElementInformation conditionCountLabel;
	conditionCountLabel.elementPosition = Vec2(57, 20);
	conditionCountLabel.elementZOrder = 0;
	_elementsInformation[gameTutorialVictoryConditionCountLabelKey] = conditionCountLabel;

	ViewElementInformation conditionImage;
	conditionImage.elementPosition = Vec2(57, 60);
	conditionImage.elementZOrder = 0;
	_elementsInformation[gameTutorialVictoryConditionImageKey] = conditionImage;

	ViewElementInformation showLevelIcon;
	showLevelIcon.elementImage = getImageNameForKey(gameTutorialShowLevelIconKey); 
	showLevelIcon.elementPosition = Vec2(500, 310);
	showLevelIcon.elementActionFinalPosition = Vec2(500, 290);
	showLevelIcon.elementZOrder = 0;
	_elementsInformation[gameTutorialShowLevelIconKey] = showLevelIcon;

	ViewElementInformation usePauseButton;
	usePauseButton.elementImage = getImageNameForKey(gameTutorialUsePauseButtonKey);
	usePauseButton.elementPosition = Vec2(startControlPosition.x + controllerOffset, startControlPosition.y + controllerOffset);
	usePauseButton.elementZOrder = 0;
	_elementsInformation[gameTutorialUsePauseButtonKey] = usePauseButton;
}

void GameViewInformationFactory::makeMainGamePausePopUpData()
{
	ViewElementInformation mainGamePausePopUpBackground;
	mainGamePausePopUpBackground.elementImage = getImageNameForKey(mainGamePauseBackgroundKey);
	mainGamePausePopUpBackground.elementPosition = getScreenCenter();
	mainGamePausePopUpBackground.elementZOrder = kMainGamePausePopUpBackgroundZOrder;
	_elementsInformation[mainGamePauseBackgroundKey] = mainGamePausePopUpBackground;

	ViewElementInformation mainGamePauseBackgroundPauseLabel;
	mainGamePauseBackgroundPauseLabel.elementImage = getImageNameForKey(mainGamePauseBackgroundPauseLabelKey);
	mainGamePauseBackgroundPauseLabel.elementPosition = Vec2(0, 90) + getScreenCenter();
	mainGamePauseBackgroundPauseLabel.elementZOrder = kMainGamePauseBackgroundPauseLabelZOrder;
	_elementsInformation[mainGamePauseBackgroundPauseLabelKey] = mainGamePauseBackgroundPauseLabel;

	ViewElementInformation mainGamePauseRegulateSoundPopUpPad;
	mainGamePauseRegulateSoundPopUpPad.elementImage = getImageNameForKey(mainGamePausePadKey);
	mainGamePauseRegulateSoundPopUpPad.elementPosition = Vec2(0, 200) + getScreenCenter();
	mainGamePauseRegulateSoundPopUpPad.elementZOrder = kMainGamePausePopUpPadZOrder;
	_elementsInformation[mainGamePausePadKey] = mainGamePauseRegulateSoundPopUpPad;
	
	ViewElementInformation mainGamePauseRegulateSoundSlider;
	mainGamePauseRegulateSoundSlider.elementImage = getImageNameForKey(mainGamePauseRegulateSoundSliderKey);
	mainGamePauseRegulateSoundSlider.elementPosition = Vec2(110, 430);
	mainGamePauseRegulateSoundSlider.elementZOrder = kMainGamePauseRegulateSoundSliderZOrder;
	_elementsInformation[mainGamePauseRegulateSoundSliderKey] = mainGamePauseRegulateSoundSlider;
	
	ViewElementInformation mainGamePauseRegulateSoundEffectsSlider;
	mainGamePauseRegulateSoundEffectsSlider.elementImage = getImageNameForKey(mainGamePauseRegulateSoundEffectsSliderKey);
	mainGamePauseRegulateSoundEffectsSlider.elementPosition = Vec2(110, 300);
	mainGamePauseRegulateSoundEffectsSlider.elementZOrder = kMainGamePauseRegulateSoundEffectsSliderZOrder;
	_elementsInformation[mainGamePauseRegulateSoundEffectsSliderKey] = mainGamePauseRegulateSoundEffectsSlider;
	
	ViewElementInformation mainGamePauseRegulateSoundCloseButton;
	mainGamePauseRegulateSoundCloseButton.elementImage = mainGamePauseCloseButtonKey;
	mainGamePauseRegulateSoundCloseButton.elementPosition = Vec2(112, 10);
	mainGamePauseRegulateSoundCloseButton.elementZOrder = kMainGamePausePopUpCloseButtonZOrder;
	_elementsInformation[mainGamePauseCloseButtonKey] = mainGamePauseRegulateSoundCloseButton;

	ViewElementInformation mainGamePauseGoToSelectLevelButton;
	mainGamePauseGoToSelectLevelButton.elementImage = mainGamePauseGoToSelectLevelButtonKey;
	mainGamePauseGoToSelectLevelButton.elementPosition = Vec2(112, -60);
	mainGamePauseGoToSelectLevelButton.elementZOrder = kMainGamePauseGoToSelectLevelButtonZOrder;
	_elementsInformation[mainGamePauseGoToSelectLevelButtonKey] = mainGamePauseGoToSelectLevelButton;
}

void GameViewInformationFactory::makeMainGameEndPopUpData()
{
	ViewElementInformation mainGameEndPopUpBackground;
	mainGameEndPopUpBackground.elementImage = getImageNameForKey(mainGameEndPopUpBackgroundKey);
	mainGameEndPopUpBackground.elementPosition = getScreenCenter();
	mainGameEndPopUpBackground.elementZOrder = kMainGameEndPopUpBackgroundZOrder;
	_elementsInformation[mainGameEndPopUpBackgroundKey] = mainGameEndPopUpBackground;

	ViewElementInformation mainGameEndPopUpWinView;
	mainGameEndPopUpWinView.elementPosition = Vec2(0, 0);
	mainGameEndPopUpWinView.elementZOrder = 0;
	_elementsInformation[mainGameEndPopUpWinViewKey] = mainGameEndPopUpWinView;

	ViewElementInformation mainGameEndPopUpLoseView;
	mainGameEndPopUpLoseView.elementPosition = Vec2(20, 0);
	mainGameEndPopUpLoseView.elementZOrder = 0;
	_elementsInformation[mainGameEndPopUpLoseViewKey] = mainGameEndPopUpLoseView;

	ViewElementInformation mainGameEndPopUpWinBeaver;
	mainGameEndPopUpWinBeaver.elementImage = getImageNameForKey(mainGameEndPopResultWinImageKey);
	mainGameEndPopUpWinBeaver.elementPosition = Vec2(30, 160) + getScreenCenter();
	mainGameEndPopUpWinBeaver.elementZOrder = kMainGameEndPopUpBeaverZOrder;
	_elementsInformation[mainGameEndPopResultWinImageKey] = mainGameEndPopUpWinBeaver;

	ViewElementInformation mainGameEndPopUpLoseBeaver;
	mainGameEndPopUpLoseBeaver.elementImage = getImageNameForKey(mainGameEndPopResultLoseImageKey);
	mainGameEndPopUpLoseBeaver.elementPosition = Vec2(-5, 160) + getScreenCenter();
	mainGameEndPopUpLoseBeaver.elementZOrder = kMainGameEndPopUpBeaverZOrder;
	_elementsInformation[mainGameEndPopResultLoseImageKey] = mainGameEndPopUpLoseBeaver;

	ViewElementInformation mainGameEndPopUpPad;
	mainGameEndPopUpPad.elementImage = getImageNameForKey(mainGameEndPopUpPadKey);
	mainGameEndPopUpPad.elementPosition = Vec2(-5, 120) + getScreenCenter();
	mainGameEndPopUpPad.elementZOrder = kMainGameEndPopUpPadZOrder;
	_elementsInformation[mainGameEndPopUpPadKey] = mainGameEndPopUpPad;

	ViewElementInformation mainGameEndPopUpPadResultLabelPad;
	mainGameEndPopUpPadResultLabelPad.elementImage = getImageNameForKey(mainGameEndPopResultLabelControllerKey);
	mainGameEndPopUpPadResultLabelPad.elementPosition = Vec2(80, 160);
	mainGameEndPopUpPadResultLabelPad.elementZOrder = 0;
	_elementsInformation[mainGameEndPopResultLabelControllerKey] = mainGameEndPopUpPadResultLabelPad;

	ViewElementInformation mainGameEndPopUpPadResultLabel;
	mainGameEndPopUpPadResultLabel.elementPosition = Vec2(110, 25);
	mainGameEndPopUpPadResultLabel.elementZOrder = 0;
	_elementsInformation[mainGameEndPopResultLabelKey] = mainGameEndPopUpPadResultLabel;

	ViewElementInformation mainGameEndPopAwardPad;
	mainGameEndPopAwardPad.elementImage = getImageNameForKey(mainGameEndPopResultLabelControllerKey);
	mainGameEndPopAwardPad.elementPosition = Vec2(80, 110);
	mainGameEndPopAwardPad.elementZOrder = 0;
	_elementsInformation[mainGameEndPopAwardPadKey] = mainGameEndPopAwardPad;

	ViewElementInformation mainGameEndPopUpPadLabel;
	mainGameEndPopUpPadLabel.elementPosition = Vec2(100, 25);
	mainGameEndPopUpPadLabel.elementZOrder = 0;
	_elementsInformation[mainGameEndPopAwardLabelKey] = mainGameEndPopUpPadLabel;

	makeMainGameEndPopUpMenuButtonsData();

	ViewElementInformation mainGameEndPopUpButton;
	mainGameEndPopUpButton.elementPosition = Vec2(getScreenCenterX(), 180);
	mainGameEndPopUpButton.elementOffset = Vec2(0, -40);
	mainGameEndPopUpButton.elementZOrder = kMainGameEndPopUpPadButtonZOrder;
	_elementsInformation[mainGameEndPopUpButtonKey] = mainGameEndPopUpButton;
}

void GameViewInformationFactory::makeMainGameEndPopUpMenuButtonsData()
{
	ViewElementInformation mainGameEndPopUpReplayLevelButton;
	mainGameEndPopUpReplayLevelButton.elementImage = mainGameEndPopUpReplayLevelButtonKey;
	mainGameEndPopUpReplayLevelButton.elementPosition = Vec2(70, 10);
	mainGameEndPopUpReplayLevelButton.elementZOrder = 0;
	_elementsInformation[mainGameEndPopUpReplayLevelButtonKey] = mainGameEndPopUpReplayLevelButton;

	ViewElementInformation mainGameEndPopUpNextLevelButton;
	mainGameEndPopUpNextLevelButton.elementImage = mainGameEndPopUpReplayLevelButtonKey;
	mainGameEndPopUpNextLevelButton.elementPosition = Vec2(70, 60);
	mainGameEndPopUpNextLevelButton.elementZOrder = 0;
	_elementsInformation[mainGameEndPopUpNextButtonKey] = mainGameEndPopUpNextLevelButton;
	
	ViewElementInformation mainGameEndPopUpGoToSelectLevelButton;
	mainGameEndPopUpGoToSelectLevelButton.elementPosition = Vec2(70, -30);
	mainGameEndPopUpGoToSelectLevelButton.elementZOrder = 0;
	_elementsInformation[mainGameEndPopUpGoToSelectLevelButtonKey] = mainGameEndPopUpGoToSelectLevelButton;
}

void GameViewInformationFactory::makeRecordsScreenData()
{
	ViewElementInformation gameRecordsBackground;
	gameRecordsBackground.elementImage = getImageNameForKey(gameRecordsBackgroundKey);
	gameRecordsBackground.elementPosition = getScreenCenter();
	gameRecordsBackground.elementZOrder = kGameRecordsBackgroundZOrder;
	_elementsInformation[gameRecordsBackgroundKey] = gameRecordsBackground;

	ViewElementInformation gameRecordsUnderWaterBackground;
	gameRecordsUnderWaterBackground.elementImage = getImageNameForKey(gameRecordsUnderWaterBackgroundKey);
	gameRecordsUnderWaterBackground.elementPosition = getScreenCenter() + Vec2(0, -315);
	gameRecordsUnderWaterBackground.elementZOrder = kGameRecordsUnderWaterBackgroundZOrder;
	_elementsInformation[gameRecordsUnderWaterBackgroundKey] = gameRecordsUnderWaterBackground;
	
	ViewElementInformation gameRecordsAnimationController;
	gameRecordsAnimationController.elementPosition = Vec2(0, 0);
	gameRecordsAnimationController.elementZOrder = kGameRecordsAnimationControllerZOrder;
	_elementsInformation[gameRecordsAnimationControllerKey] = gameRecordsAnimationController;

	makeGameRecordsAnimationData();

	ViewElementInformation gameRecordsFishes;
	gameRecordsFishes.elementPosition = Vec2(0, 0);
	gameRecordsFishes.elementZOrder = kGameRecordsFishesZOrder;
	_elementsInformation[gameRecordsFishesKey] = gameRecordsFishes;

	makeGameRecordsFishesData();

}

void GameViewInformationFactory::makeGameRecordsAnimationData()
{
	ViewElementInformation gameRecordsBoardController;
	gameRecordsBoardController.elementPosition = Vec2(getScreenCenterX(), 1180);
	gameRecordsBoardController.elementActionFinalPosition = Vec2(getScreenCenterX(), 700);
	gameRecordsBoardController.elementOffset = Vec2(0, -70);
	gameRecordsBoardController.elementZOrder = kGameRecordsBoardZOrder;
	_elementsInformation[gameRecordsBoardControllerKey] = gameRecordsBoardController;

	ViewElementInformation gameRecordsBoardPad;
	gameRecordsBoardPad.elementImage = getImageNameForKey(gameRecordsBoardPadKey);
	gameRecordsBoardPad.elementPosition = Vec2(0, -110);
	gameRecordsBoardPad.elementZOrder = 0;
	_elementsInformation[gameRecordsBoardPadKey] = gameRecordsBoardPad;

	ViewElementInformation gameRecordsBoardUnderWaterPart;
	gameRecordsBoardUnderWaterPart.elementImage = getImageNameForKey(gameRecordsBoardUnderWaterPartKey);
	gameRecordsBoardUnderWaterPart.elementPosition = Vec2(getScreenCenterX(), -120);
	gameRecordsBoardUnderWaterPart.elementActionFinalPosition = Vec2(getScreenCenterX(), 70);
	gameRecordsBoardUnderWaterPart.elementZOrder = 0;
	_elementsInformation[gameRecordsBoardUnderWaterPartKey] = gameRecordsBoardUnderWaterPart;

	ViewElementInformation gameRecordsBoardPlayerLabelName;
	gameRecordsBoardPlayerLabelName.elementPosition = Vec2(30, 35);
	gameRecordsBoardPlayerLabelName.elementZOrder = 0;
	_elementsInformation[gameRecordsBoardPlayerNameLabelKey] = gameRecordsBoardPlayerLabelName;

	ViewElementInformation gameRecordsGoToMainMenuButton;
	gameRecordsGoToMainMenuButton.elementImage = gameRecordsGoToMainMenuButtonKey;
	gameRecordsGoToMainMenuButton.elementPosition = Vec2(0, -350);
	gameRecordsGoToMainMenuButton.elementZOrder = 0;
	_elementsInformation[gameRecordsGoToMainMenuButtonKey] = gameRecordsGoToMainMenuButton;

	ViewElementInformation gameRecordsBeaver;
	gameRecordsBeaver.elementImage = getImageNameForKey(gameRecordsBeaverKey);
	gameRecordsBeaver.elementPosition = Vec2(getScreenCenterX() + 190, 1000);
	gameRecordsBeaver.elementActionFinalPosition = Vec2(getScreenCenterX() + 190, 270);
	gameRecordsBeaver.elementZOrder = kGameRecordsBeaverZOrder;
	_elementsInformation[gameRecordsBeaverKey] = gameRecordsBeaver;

	ViewElementInformation gameRecordsBeaverClock;
	gameRecordsBeaverClock.elementImage = getImageNameForKey(gameRecordsClockKey);
	gameRecordsBeaverClock.elementPosition = Vec2(90, 275);
	gameRecordsBeaverClock.elementZOrder = kGameRecordsBeaverZOrder;
	_elementsInformation[gameRecordsClockKey] = gameRecordsBeaverClock;

}

void GameViewInformationFactory::makeGameRecordsFishesData()
{
	ViewElementInformation gameRecordsFish1;
	gameRecordsFish1.elementImage = getImageNameForKey(gameRecordsFish1Key);
	gameRecordsFish1.elementPosition = Vec2(280, 80);
	gameRecordsFish1.elementActionFinalPosition = Vec2(280, 50);
	gameRecordsFish1.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[gameRecordsFish1Key] = gameRecordsFish1;

	ViewElementInformation gameRecordsFish2;
	gameRecordsFish2.elementImage = getImageNameForKey(gameRecordsFish2Key);
	gameRecordsFish2.elementPosition = Vec2(140, 50);
	gameRecordsFish2.elementActionFinalPosition = Vec2(140, 90);
	gameRecordsFish2.elementZOrder = kStartGameRegulateSoundPopUpZOrder;
	_elementsInformation[gameRecordsFish2Key] = gameRecordsFish2;
}

void GameViewInformationFactory::makeDevelopersScreenData()
{
	ViewElementInformation gameDevelopersBackground;
	gameDevelopersBackground.elementImage = getImageNameForKey(gameDevelopersBackgroundKey);
	gameDevelopersBackground.elementPosition = getScreenCenter();
	gameDevelopersBackground.elementZOrder = kGameDevelopersBackgroundZOrder;
	_elementsInformation[gameDevelopersBackgroundKey] = gameDevelopersBackground;

	ViewElementInformation gameDevelopersUnderWaterBackground;
	gameDevelopersUnderWaterBackground.elementImage = getImageNameForKey(gameDevelopersUnderWaterBackgroundKey);
	gameDevelopersUnderWaterBackground.elementPosition = getScreenCenter() + Vec2(0, -315);
	gameDevelopersUnderWaterBackground.elementZOrder = kGameDevelopersUnderWaterBackgroundZOrder;
	_elementsInformation[gameDevelopersUnderWaterBackgroundKey] = gameDevelopersUnderWaterBackground;

	ViewElementInformation gameDevelopersFishes;
	gameDevelopersFishes.elementPosition = Vec2(0, -10);
	gameDevelopersFishes.elementZOrder = kGameDevelopersFishesZOrder;
	_elementsInformation[gameDevelopersFishesKey] = gameDevelopersFishes;

	ViewElementInformation gameDevelopersAnimationController;
	gameDevelopersAnimationController.elementPosition = Vec2(0, 0);
	gameDevelopersAnimationController.elementZOrder = kGameDevelopersAnimationControllerZOrder;
	_elementsInformation[gameDevelopersAnimationControllerKey] = gameDevelopersAnimationController;
	
	makeGameDevelopersAnimationData();

}

void GameViewInformationFactory::makeGameDevelopersAnimationData()
{
	
	ViewElementInformation gameDevelopersBoardController;
	gameDevelopersBoardController.elementPosition = Vec2(getScreenCenterX(), 1180);
	gameDevelopersBoardController.elementActionFinalPosition = Vec2(getScreenCenterX(), 600);
	gameDevelopersBoardController.elementZOrder = kGameDevelopersBoardZOrder;
	_elementsInformation[gameDevelopersBoardControllerKey] = gameDevelopersBoardController;

	makeGameDevelopersBoardData();

	ViewElementInformation gameDevelopersBeaver;
	gameDevelopersBeaver.elementImage = getImageNameForKey(gameDevelopersBeaverKey);
	gameDevelopersBeaver.elementPosition = Vec2(770, 1170);
	gameDevelopersBeaver.elementActionFinalPosition = Vec2(770, 595);
	gameDevelopersBeaver.elementZOrder = kGameDevelopersBeaverZOrder;
	_elementsInformation[gameDevelopersBeaverKey] = gameDevelopersBeaver;

	ViewElementInformation gameDevelopersBeaverClock;
	gameDevelopersBeaverClock.elementImage = getImageNameForKey(gameDevelopersClockKey);
	gameDevelopersBeaverClock.elementPosition = Vec2(150, 84);
	gameDevelopersBeaverClock.elementZOrder = kGameRecordsBeaverZOrder;
	_elementsInformation[gameDevelopersClockKey] = gameDevelopersBeaverClock;

}

void GameViewInformationFactory::makeGameDevelopersBoardData()
{
	ViewElementInformation gameDevelopersBoardPad;
	gameDevelopersBoardPad.elementImage = getImageNameForKey(gameDevelopersBoardPadKey);
	gameDevelopersBoardPad.elementPosition = Vec2(0, -60);
	gameDevelopersBoardPad.elementZOrder = 0;
	_elementsInformation[gameDevelopersBoardPadKey] = gameDevelopersBoardPad;

	ViewElementInformation gameDevelopersBoardUnderWaterPart;
	gameDevelopersBoardUnderWaterPart.elementImage = getImageNameForKey(gameDevelopersBoardUnderWaterPartKey);
	gameDevelopersBoardUnderWaterPart.elementPosition = Vec2(getScreenCenterX(), -120);
	gameDevelopersBoardUnderWaterPart.elementActionFinalPosition = Vec2(getScreenCenterX(), 70);
	gameDevelopersBoardUnderWaterPart.elementZOrder = 0;
	_elementsInformation[gameDevelopersBoardUnderWaterPartKey] = gameDevelopersBoardUnderWaterPart;

	ViewElementInformation gameDevelopersBoardPlacePad;
	gameDevelopersBoardPlacePad.elementImage = getImageNameForKey(gameDevelopersBoardPlacePadKey);
	gameDevelopersBoardPlacePad.elementPosition = Vec2(0, 0);
	gameDevelopersBoardPlacePad.elementZOrder = 0;
	_elementsInformation[gameDevelopersBoardPlacePadKey] = gameDevelopersBoardPlacePad;

	makeGameDevelopersPositionsData();
	
	ViewElementInformation gameDevelopersFunctionLabel;
	gameDevelopersFunctionLabel.elementPosition = Vec2(100, 37);
	gameDevelopersFunctionLabel.elementZOrder = 0;
	_elementsInformation[gameDevelopersFunctionLabelKey] = gameDevelopersFunctionLabel;
	
	ViewElementInformation gameDevelopersNameLabel;
	gameDevelopersNameLabel.elementPosition = Vec2(100, 23);
	gameDevelopersNameLabel.elementZOrder = 0;
	_elementsInformation[gameDevelopersNameLabelKey] = gameDevelopersNameLabel;

	ViewElementInformation gameDevelopersGoToMainMenuButton;
	gameDevelopersGoToMainMenuButton.elementImage = gameDevelopersGoToMainMenuButtonKey;
	gameDevelopersGoToMainMenuButton.elementPosition = Vec2(0, -300);
	gameDevelopersGoToMainMenuButton.elementZOrder = kGameDevelopersGoToMainMenuButtonZOrder;
	_elementsInformation[gameDevelopersGoToMainMenuButtonKey] = gameDevelopersGoToMainMenuButton;

}

void GameViewInformationFactory::makeGameDevelopersPositionsData()
{
	ViewElementInformation gameDeveloperProgrammer;
	gameDeveloperProgrammer.elementPosition = Vec2(0, -80);
	gameDeveloperProgrammer.elementZOrder = 0;
	_elementsInformation[gameDeveloperProgrammerKey] = gameDeveloperProgrammer;
	
	ViewElementInformation gameDeveloperDesigner;
	gameDeveloperDesigner.elementPosition = Vec2(0, -150);
	gameDeveloperDesigner.elementZOrder = 0;
	_elementsInformation[gameDeveloperDesignerKey] = gameDeveloperDesigner;

	ViewElementInformation gameDevelopersEmail;
	gameDevelopersEmail.elementPosition = Vec2(0, -220);
	gameDevelopersEmail.elementZOrder = 0;
	_elementsInformation[gameDevelopersEmailKey] = gameDevelopersEmail;
}

void GameViewInformationFactory::makeFinalScreenData()
{
	ViewElementInformation finalScreenBackground;
	finalScreenBackground.elementImage = getImageNameForKey(finalScreenBackgroundKey);
	finalScreenBackground.elementPosition = getScreenCenter();
	finalScreenBackground.elementZOrder = kFinalSreenBackgroundZOrder;
	_elementsInformation[finalScreenBackgroundKey] = finalScreenBackground;

	ViewElementInformation finalScreenAnimationController;
	finalScreenAnimationController.elementPosition = Vec2(0, 0);
	finalScreenAnimationController.elementZOrder = kFinalSreenAnimationControllerZOrder;
	_elementsInformation[finalScreenAnimationControllerKey] = finalScreenAnimationController;

	makeFinalScreenAnimationData();

	ViewElementInformation finalScreenGoToRecordsButton;
	finalScreenGoToRecordsButton.elementImage = finalScreenGoToRecordsButtonKey;
	finalScreenGoToRecordsButton.elementPosition = Vec2(getScreenCenterX(), 50);
	finalScreenGoToRecordsButton.elementZOrder = kFinalSreenGoToRecordsButtonZOrder;
	_elementsInformation[finalScreenGoToRecordsButtonKey] = finalScreenGoToRecordsButton;

}

void GameViewInformationFactory::makeFinalScreenAnimationData()
{
	ViewElementInformation finalScreenClock;
	finalScreenClock.elementImage = getImageNameForKey(finalScreenClockKey);
	finalScreenClock.elementPosition = Vec2(220, 420);
	finalScreenClock.elementZOrder = 0;
	_elementsInformation[finalScreenClockKey] = finalScreenClock;

	ViewElementInformation finalScreenBeaverPad;
	finalScreenBeaverPad.elementPosition = Vec2(480, 100);
	finalScreenBeaverPad.elementActionFinalPosition = Vec2(getScreenCenterX(), 100);
	finalScreenBeaverPad.elementOffset = Vec2(0, 200);
	finalScreenBeaverPad.elementZOrder = 0;
	_elementsInformation[finalScreenBeaverKey] = finalScreenBeaverPad;

	ViewElementInformation beaverRightHand;
	beaverRightHand.elementImage = getImageNameForKey(finalScreenBeaverRightHandKey);
	beaverRightHand.elementPosition = Vec2(90, 240);
	beaverRightHand.elementZOrder = kFinalSreenBeaverRightHandZOrder;
	_elementsInformation[finalScreenBeaverRightHandKey] = beaverRightHand;

	ViewElementInformation beaverLeftHand;
	beaverLeftHand.elementImage = getImageNameForKey(finalScreenBeaverLeftHandKey);
	beaverLeftHand.elementPosition = Vec2(-230, 240);
	beaverLeftHand.elementZOrder = kFinalSreenBeaverLeftHandZOrder;
	_elementsInformation[finalScreenBeaverLeftHandKey] = beaverLeftHand;

	ViewElementInformation beaverBody;
	beaverBody.elementImage = getImageNameForKey(finalScreenBeaverBodyKey);
	beaverBody.elementPosition = Vec2(0, 85);
	beaverBody.elementActionFinalPosition = Vec2(getScreenCenterX(), 220);
	beaverBody.elementZOrder = kFinalSreenBeaverBodyZOrder;
	_elementsInformation[finalScreenBeaverBodyKey] = beaverBody;

	ViewElementInformation beaverEyesPad;
	beaverEyesPad.elementPosition = Vec2(-80, 270);
	beaverEyesPad.elementZOrder = kFinalSreenBeaverEyesZOrder;
	_elementsInformation[finalScreenBeaverEyesKey] = beaverEyesPad;

	ViewElementInformation beaverRightEye;
	beaverRightEye.elementImage = getImageNameForKey(finalScreenBeaverRightEyeKey);
	beaverRightEye.elementPosition = Vec2(15, 35);
	beaverRightEye.elementZOrder = 0;
	_elementsInformation[finalScreenBeaverRightEyeKey] = beaverRightEye;

	ViewElementInformation beaverLeftEye;
	beaverLeftEye.elementImage = getImageNameForKey(finalScreenBeaverLeftEyeKey);
	beaverLeftEye.elementPosition = Vec2(-80, 40);
	beaverLeftEye.elementZOrder = 0;
	_elementsInformation[finalScreenBeaverLeftEyeKey] = beaverLeftEye;

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


