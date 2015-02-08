#pragma once

#include "GameSystemInterface.h"

class GameBoard;
class GameTimeStepController;

class WinGameSystem :public GameSystemInterface
{
public:
	WinGameSystem(GameBoard *aGameBoard);
	~WinGameSystem(void);

	void updateSystem(float deltaTime);

private:

	GameBoard *_gameBoard;
	GameTimeStepController *_gameTimeStepController;

	bool loseGameChecker();

};

