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
	kGoToPopUp3,
	kClosePopUp4,
	kEvent5,
};

enum PopUpType
{
	kPopUp1,
	kPopUp2,
	kPopUp3,
};

enum TetraminoType
{
	kTetramino1,
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

