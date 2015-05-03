#pragma once

enum LoadingSreenZOrdes
{
	kLoadingBackgroundZOrder,
	kLoadingGameWaveZOrder,
	kLoadingGameNameZOrder,
	kLoadingBeaverZOrder,
	kLoadingClockZOrder,
};

enum StartGameSreenZOrdes
{
	kStartGameBackgroundZOrder,
	kStartGameBeaverZOrder,
	kStartGameMenuZOrder,
	kStartGameFishesZOrder,
	kStartGameRegulateSoundPopUpZOrder,
};

enum StartGameRegulateSoundPopUpZOrders
{
	kStartGameRegulateSoundPopUpPadZOrder,
	kStartGameRegulateSoundSliderZOrder,
	kStartGameRegulateSoundEffectsSliderZOrder,
	kStartGameRegulateSoundPopUpCloseButtonZOrder,
};

enum SelectGameLevelScreenZOrders
{
	kSelectLevelMenuZOrder,
	kSelectLevelScenePlayerStatusControllerZOrder,
	kSelectLevelSceneBackButtonZOrder,
	kPlayerCreatorControllerZOrder,
	kSelectLevelSceneBeaverTalkZOrder,
};

enum SelectGameLevelPlayerStatusZOrders
{
	kSelectLevelPlayerStatusPadZOrder,
	kSelectLevelPlayerStatusNameZOrder,
	kSelectLevelPlayerStatusScoreZOrder,
};

enum PlayerCreatorZOrders
{
	kPlayerCreatorBackgroundZOrder,
	kPlayerCreatorPadZOrder,
	kPlayerCreatorInputZOrder,
	kPlayerCreatorTextZOrder,
};

enum MainGameScreenZOrders
{
	kWorldControllerZOrder,
	kHudControllerZOrder,
	kMainGamePausePopUpZOrder,
	kMainGameEndPopUpZOrder,
};

enum MainGameWorldZOrders
{
	kMainGameBackgroundZOrder,
	kMainGameBoardZOrder,
	kMainGameAnimationZOrder,
};

enum MainGameHudsZOrders
{
	kMainGameHudsBackgroundZOrder,
	kMainGamePlayerActionControllerZOrder,
	kMainGamePlayerScoreControllerZOrder,
	kMainGamePlayerVictoryConditionZOrder,
	kMainGamePlayerSpellsControllerZOrder,
};

enum MainGamePlayerScoreControllerZOrders
{
	kMainGamePlayerScoreBackgroundZOrder,
	kMainGamePlayerScoreCountZOrder,
};

enum MainGamePlayerVictoryConditionZOrders
{
	kVictoryConditionHudImageZOrder,
	kVictoryConditionStateZOrder,
};

enum SpellViewZOrders
{
	kSpellIconImageZOrder,
	kSpellCostLabelZOrder,
	kSpellButtonLabelZOrder,
};

enum RemoveCurrentDetailSpellViewZOrders
{
	kRocketForRemoveDetailZOrder,
	kDetailForRemoveCurrentDetailZOrder,
	kExplosionsForRemoveDetailZOrder,
};

enum MainGamePausePopUpZOrders
{
	kMainGamePausePopUpBackgroundZOrder,
	kMainGamePauseBackgroundPauseLabelZOrder,
	kMainGamePausePopUpPadZOrder,
	kMainGamePauseRegulateSoundSliderZOrder,
	kMainGamePauseRegulateSoundEffectsSliderZOrder,
	kMainGamePausePopUpCloseButtonZOrder,
	kMainGamePauseGoToSelectLevelButtonZOrder,
};

enum MainGameEndPopUpZOrders
{
	kMainGameEndPopUpPadZOrder,
	kMainGameEndPopUpPadButtonZOrder,
};

enum GameRecordsSreenZOrdes
{
	kGameRecordsBackgroundZOrder,
	kGameRecordsUnderWaterBackgroundZOrder,
	kGameRecordsAnimationControllerZOrder,
	kGameRecordsFishesZOrder,
	kGameRecordsGoToMainMenuButtonZOrder,
};

enum GameRecordsAnimationElementsZOrdes
{
	kGameRecordsBoardZOrder,
	kGameRecordsBeaverZOrder,
};

enum GameDevelopersSreenZOrdes
{
	kGameDevelopersBackgroundZOrder,
	kGameDevelopersUnderWaterBackgroundZOrder,
	kGameDevelopersAnimationControllerZOrder,
	kGameDevelopersFishesZOrder,
	kGameDevelopersGoToMainMenuButtonZOrder,
};

enum GameDevelopersAnimationElementsZOrdes
{
	kGameDevelopersBoardZOrder,
	kGameDevelopersBeaverZOrder,
};