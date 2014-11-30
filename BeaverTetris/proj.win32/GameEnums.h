#pragma once

enum GameState
{
	kLoadGame,
	kStartGame,
	kSelectLevel,
	kPlayGame,
	kDevelopers,
	kRecords,
};

enum TransitionType
{
	kTransition1,
	kTransition2,
	kTransition3,
	kTransition4,
	kTransition5,
	kTransition6,
};

enum EventType
{
	kGoToInitualSceneEvent,
	kGoToSceneEvent,
	kGoToPreviousSceneEvent,
	kGoToPopUp,
	kClosePopUp,
	kPlayerActionInGameEvent,
};

enum PopUpType
{
	kRegulateSoundPopUp,
	kWinGamePopUp,
	kLoseGameUp,
	kWinAllGamePopUp,
	kPauseGamePopUp,
};

enum TetraminoType
{
	kTetraminoEmpty,
	kTetramino2,
	kTetramino3,
};

enum VictoryConditionType
{
	kVictoryCondition1,
	kVictoryCondition2,
	kVictoryCondition3,
};

enum SpellType
{
	kSpell1,
	kSpell2,
	kSpell3,
	kSpell4,
};

enum GameEventType
{
	kGameEvent1,
	kGameEvent2,
};

enum DirectionType
{
	kTopDirection,
	kRightDirection,
	kBottomDirection,
	kLeftDirection,
	kEndDirection,
};

enum PlayerActionInGameType
{
	kTurnDetailLeft,
	kTurnDetailRight,
	kAccelerateDetail,
	kRotateDetail,
};
