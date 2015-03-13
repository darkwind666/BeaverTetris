#pragma once

enum LoadingSreenZOrdes
{
	kLoadingBackgroundZOrder,
	kLoadingBeaverZOrder,
	kLoadingClockZOrder,
};

enum StartGameSreenZOrdes
{
	kStartGameBackgroundZOrder,
	kStartGameBeaverZOrder,
	kStartGameMenuZOrder,
	kBeaverClockArrowZOrder,
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
	kPlayerCreatorControllerZOrder,
	kSelectLevelSceneBackButtonZOrder,
};

enum SelectGameLevelPlayerStatusZOrders
{
	kSelectLevelPlayerStatusPadZOrder,
	kSelectLevelPlayerStatusNameZOrder,
	kSelectLevelPlayerStatusScoreZOrder,
};

enum PlayerCreatorZOrders
{
	kPlayerCreatorPadZOrder,
	kPlayerCreatorTextZOrder,
	kPlayerCreatorInputZOrder,
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
};

enum RemoveCurrentDetailSpellViewZOrders
{
	kRocketForRemoveDetailZOrder,
	kDetailForRemoveCurrentDetailZOrder,
	kExplosionsForRemoveDetailZOrder,
};

enum MainGamePausePopUpZOrders
{
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
	kGameRecordsAnimationControllerZOrder,
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
	kGameDevelopersAnimationControllerZOrder,
	kGameDevelopersGoToMainMenuButtonZOrder,
};

enum GameDevelopersAnimationElementsZOrdes
{
	kGameDevelopersBoardZOrder,
	kGameDevelopersBeaverZOrder,
};