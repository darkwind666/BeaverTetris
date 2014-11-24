#pragma once

class CurrentPlayerDataSource;
class GamePlayersDatabase;
class GameLevelsDataSource;
class TetraminosCharacteristicsDataSource;

class GameDataFactory
{
public:
	GameDataFactory(void);
	~GameDataFactory(void);

	void createGameData(void);
	void createGameLogic(void);

private:

	 CurrentPlayerDataSource *_currentPlayerDataSource;
     GamePlayersDatabase *_gamePlayersDatabase;
     GameLevelsDataSource *_gameLevelsDataSource;
     TetraminosCharacteristicsDataSource *_tetraminosCharacteristicsDataSource;

};

