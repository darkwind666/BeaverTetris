#pragma once

class WinGameSystem;
class CurrentPlayerDataSource;
class GamePlayersDatabase;
class CurrentLevelDataSource;
class GameAnalyticController;

class GameResultDelegate
{
public:
	GameResultDelegate(WinGameSystem *aWinGameSystem);
	~GameResultDelegate(void);

	void gameWasEnded();

private:

	WinGameSystem *_winGameSystem;
	CurrentPlayerDataSource *_currentPlayerDataSource;
	GamePlayersDatabase *_gamePlayersDatabase;
	CurrentLevelDataSource *_currentLevelDataSource;
	GameAnalyticController *_gameAnalyticController;

	void giveResultToPlayer();
	void writePlayerToDatabaseIfFinalLevel();
	void restorePlayerScore();

};

