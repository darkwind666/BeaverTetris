#pragma once

#include "GameSystemInterface.h"
#include "CurrentPlayerDataSource.h"
#include "CurrentLevelDataSource.h"
#include "GameBoard.h"

class WinGameSystem :public GameSystemInterface
{
public:
	WinGameSystem(CurrentPlayerDataSource *aCurrentPlayerDataSource, CurrentLevelDataSource *aCurrentLevelDataSource, GameBoard *aGameBoard);
	~WinGameSystem(void);

	void updateSystem(float deltaTime);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	CurrentLevelDataSource *_currentLevelDataSource;
	GameBoard *_gameBoard;

	bool loseGameChecker();

};

