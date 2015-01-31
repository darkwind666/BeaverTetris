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
};

enum MainGamePlayerScoreControllerZOrders
{
	kMainGamePlayerScoreBackgroundZOrder,
	kMainGamePlayerScoreCountZOrder,
};