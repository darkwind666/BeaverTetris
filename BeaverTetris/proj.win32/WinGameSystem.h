#pragma once

#include "GameSystemInterface.h"
#include "CurrentPlayerDataSource.h"
#include "CurrentLevelWinResultDataSource.h"
#include "GameBoard.h"

class WinGameSystem :public GameSystemInterface
{
public:
	WinGameSystem(CurrentPlayerDataSource *aCurrentPlayerDataSource, CurrentLevelWinResultDataSource *aCurrentLevelWinResultDataSource, GameBoard *aGameBoard);
	~WinGameSystem(void);

	void updateSystem(float deltaTime);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	CurrentLevelWinResultDataSource *_currentLevelWinResultDataSource;
	GameBoard *_gameBoard;

	bool loseGameChecker();

};

