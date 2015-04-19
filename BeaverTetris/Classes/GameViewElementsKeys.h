#pragma once

#include <string>

using namespace std;

const string loadingGameBackgroundKey = string("LoadingScreenBackground");
const string loadingGameBeaverKey = string("LoadingScreenBeaver");
const string loadingGameClockKey = string("LoadingScreenClockCover");
const string loadingGameNameKey = string("LoadingScreenGameName");
const string loadingGameWaveKey = string("LoadingScreenWaves");

const string startGameMenuBackgroundKey = string("MenuScreenBackground");
const string startGameBeaverKey = string("MenuScreenBeaver");

const string startGameFishesKey = string("startGameFishes");
const string startGameFish1Key = string("MenuScreenFish");
const string startGameFish2Key = string("MenuScreenFish2");
const string startGameFish3Key = string("MenuScreenFish3");

const string startGameMenuKey = string("MenuScreenStaircase");
const string createNewGameButtonKey = string("MenuScreenNewGame");
const string selectGameLevelButtonKey = string("MenuScreenSelectLevel");
const string goToGameRecordsButtonKey = string("MenuScreenRecords");
const string getSoundRegulatorsButtonKey = string("MenuScreenSetting");
const string goToDevelopersButtonKey = string("MenuScreenAuthors");

const string startGameRegulateSoundPopUpKey = string("startGameRegulateSoundPopUp");
const string startGameRegulateSoundPadKey = string("startGameRegulateSoundPad");
const string startGameRegulateSoundSliderKey = string("startGameRegulateSoundSlider");
const string startGameRegulateSoundEffectsSliderKey = string("startGameRegulateSoundEffectsSlider");
const string startGameRegulateSoundCloseButtonKey = string("startGameRegulateSoundCloseButton");

const string selectLevelBackgroundKey = string("SelectLevelScreenBackground");
const string selectLevelBackgroundRightKey = string("SelectLevelRightGround");
const string selectLevelBackgroundLeftKey = string("SelectLevelLeftGround");

const string selectLevelBeaverTalkKey = string("SelectLevelScreenTalk");

const string selectLevelMenuKey = string("selectLevelMenu");

const string gameLevel1Key = string("StartLevel");
const string gameLevel2Key = string("StartBlockCollectionLevel");
const string gameLevel3Key = string("StartGoodTimeLevel");
const string gameLevel4Key = string("StartBossLevel");
const string gameLevel5Key = string("MiddleLevel");
const string gameLevel6Key = string("MiddleGoodTimeLevel");
const string gameLevel7Key = string("MiddleBossLevel");
const string gameLevel8Key = string("EndBlockCollectionLevel");
const string gameLevel9Key = string("EndLevel");
const string gameLevel10Key = string("EndBossLevel");

const string levelCompletedSignKey = string("LevelCompletedSign");
const string selectLevelBeaverOnRaftKey = string("SelectLevelScreeBeaverOnRaft");

const string selectLevelScenePlayerStatusControllerKey = string("selectLevelScenePlayerStatusController");
const string selectLevelScenePlayerStatusPadKey = string("selectLevelScenePlayerStatusPad");
const string selectLevelScenePlayerStatusNameKey = string("selectLevelScenePlayerStatusName");
const string selectLevelScenePlayerStatusScoreKey = string("selectLevelScenePlayerStatusScore");

const string playerCreatorControllerKey = string("playerCreatorController");
const string playerCreatorControllerPadKey = string("playerCreatorControllerPad");
const string playerCreatorControllerTextKey = string("playerCreatorControllerText");
const string playerCreatorControllerInputKey = string("playerCreatorControllerInput");

const string selectLevelSceneBackButtonKey = string("selectLevelSceneBackButton");

const string gameWorldControllerKey = string("gameWorldController");
const string mainGameBackgroundControllerKey = string("MainGameBackground");
const string mainGameBackgroundPadKey = string("MainGamePad");
const string mainGameBoardControllerKey = string("mainGameBoardController");
const string tetraminoLivesCountViewKey = string("tetraminoLivesCountView");

const string redTetraminoKey = string("redTetramino");
const string greenTetraminoKey = string("greenTetramino");
const string blueTetraminoKey = string("blueTetramino");
const string goldTetraminoKey = string("goldTetramino");
const string blackTetraminoKey = string("blackTetramino");
const string queenTetraminoKey = string("queenBoss");
const string princessTetraminoKey = string("princessesBoss");
const string kingTetraminoKey = string("kingBoss");

const string mainGameAnimationControllerKey = string("mainGameAnimationController");

const string gameHudControllerKey = string("gameHudController");
const string gameHudBackgroundKey = string("gameHudBackground");
const string playerActionControllerKey = string("playerActionController");

const string playerControlInactiveImageKey = string("PlayerActionInactiveButton");
const string playerControlActiveImageKey = string("PlayerActionActiveButton");
const string rotateDetailControlKey = string("rotateDetailControl");
const string accelerateDetailControlKey = string("accelerateDetailControl");
const string moveDetailLeftControlKey = string("moveDetailLeftControl");
const string moveDetailRightControlKey = string("moveDetailRightControl");

const string playerScoreControllerKey = string("playerScoreController");
const string playerScoreControllerBackgroundKey = string("MainGamePlayerScorePad");
const string playerScoreControllerCountKey = string("playerScoreControllerCount");

const string victoryConditionHudControllerKey = string("victoryConditionHudController");
const string victoryConditionPadImageKey = string("VictoryConditionPad");
const string victoryConditionHudImageKey = string("victoryConditionHudImage");
const string victoryConditionHudStateKey = string("victoryConditionHudState");

const string playerSpellsControllerKey = string("playerSpellsController");
const string playerSpellImageKey = string("UnavailableSpellIcon");
const string playerSpellCostLabelKey = string("playerSpellCostLabel");

const string removeCurrentDetailSpellKey = string("rocketSpell");
const string firestormSpellKey = string("firestormSpell");
const string removeRandomTetraminosSpellKey = string("randomExplosionsSpell");
const string cohesionSpellKey = string("cohesionSpell");

const string rocketForRemoveCurrentDetailSpellKey = string("RocketForRemoveCurrentDetailSpell");
const string explosionsForRemoveCurrentDetailSpellKey = string("ExplosionsForRemoveCurrentDetailSpell");
const string detailForRemoveCurrentDetailSpellKey = string("DetailForRemoveCurrentDetailSpell");

const string meteorForFirestormSpellKey = string("MeteorForFirestormSpell");

const string placeDetailsIconKey = string("PlaceDetails");
const string remainSomeTimeIconKey = string("RemainTime");
const string removeSomeTetraminosKey = string("RemoveTetraminos");
const string killBossKey = string("Boss");

const string accelerateEventKey = string("accelerateEvent");
const string fallDetailsEventKey = string("fallDetailsEvent");

const string pauseGameViewControllerKey = string("MainGamePauseButton");
const string mainGamePausePopUpKey = string("MainGamePausePopUp");
const string mainGamePausePadKey = string("MainGamePausePad");
const string mainGamePauseRegulateSoundSliderKey = string("mainGamePauseRegulateSoundSlider");
const string mainGamePauseRegulateSoundEffectsSliderKey = string("mainGamePauseRegulateSoundEffectsSlider");
const string mainGamePauseCloseButtonKey = string("mainGamePauseRegulateSoundCloseButton");
const string mainGamePauseGoToSelectLevelButtonKey = string("mainGamePauseGoToSelectLevelButton");

const string mainGameEndPopUpKey = string("MainGameEndPopUp");
const string mainGameEndPopUpPadKey = string("MainGameEndPad");
const string mainGameEndPopUpButtonKey = string("MainGameEndButton");

const string gameRecordsBackgroundKey = string("gameRecordsBackground");
const string gameRecordsAnimationControllerKey = string("GameRecordsAnimationController");
const string gameRecordsBoardControllerKey = string("GameRecordsBoardController");
const string gameRecordsBoardPlayerNameLabelKey = string("gameRecordsBoardPlayerNameLabel");
const string gameRecordsBoardPlayerScoreLabelKey = string("gameRecordsBoardPlayerScoreLabel");
const string gameRecordsBeaverKey = string("gameRecordsBeaver");
const string gameRecordsGoToMainMenuButtonKey = string("gameRecordsGoToMainMenuButton");

const string gameDevelopersBackgroundKey = string("gameDevelopersBackground");
const string gameDevelopersAnimationControllerKey = string("GameDevelopersAnimationController");
const string gameDevelopersBoardControllerKey = string("GameDevelopersBoardController");
const string gameDeveloperProgrammerKey = string("gameDeveloperProgrammer");
const string gameDeveloperDesignerKey = string("gameDeveloperDesigner");
const string gameDevelopersFunctionLabelKey = string("gameDevelopersFunctionLabel");
const string gameDevelopersNameLabelKey = string("gameDevelopersNameLabel");
const string gameDevelopersBeaverKey = string("gameDevelopersBeaver");
const string gameDevelopersGoToMainMenuButtonKey = string("gameDevelopersGoToMainMenuButton");
