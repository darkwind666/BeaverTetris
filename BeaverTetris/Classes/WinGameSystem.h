#pragma once

#include "GameSystemInterface.h"

class GameBoard;
class GameTimeStepController;
class VictoryConditionInterface;

class WinGameSystem :public GameSystemInterface
{
public:
	WinGameSystem();
	~WinGameSystem(void);

	void updateSystem(float deltaTime);

private:

	GameBoard *_gameBoard;
	GameTimeStepController *_gameTimeStepController;
	VictoryConditionInterface *_currentVictoryCondition;

	void checkWinGameState();
	void checkLoseGameState();
	bool loseGameChecker();

};

