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
	kGoToNextLevelSceneEvent,
	kGoToPopUp,
	kClosePopUp,
	kPlayerActionInGameEvent,
};

enum PopUpType
{
	kRegulateSoundPopUp,
	kPauseGamePopUp,
	kEndGamePopUp,
};

enum TetraminoType
{
	kTetraminoEmpty,
	kTetraminoRed,
	kTetraminoGreen,
	kTetraminoBlue,
	kTetraminoGold,
	kTetraminoBlack,
	kTetraminoBossQueen,
	kTetraminoBossPrincess,
	kTetraminoBossKing,
};

enum TetraminoDetailType
{
	kTetraminoDetail1,
	kTetraminoDetail2,
	kTetraminoDetail3,
	kTetraminoDetail4,
	kTetraminoDetail5,
	kTetraminoDetail6,
	kTetraminoDetail7,
	kTetraminoDetail8,
};

enum VictoryConditionType
{
	kPlaceSomeDetailsCondition,
	kRemainSomeTimeCondition,
	kRemoveSomeTetraminosCondition,
	kWinBossCondition,
};

enum SpellType
{
	kRocketSpell,
	kRandomExplosionsSpell,
	kFirestormSpell,
	kCohessionSpell,
	kBadSpell,
	kAddLineToBoardBottomSpell,
	kDamageToPlayerSpell,
	kSpellEnd,
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

enum BossMovementType
{
	kTurnLeftMovement,
	kTurnRightMovement,
	kTurnUpMovement,
	kTurnDownMovement,
	kIdleMovement,
};
