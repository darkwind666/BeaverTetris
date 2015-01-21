#pragma once

#include <string>

class CurrentPlayerDataSource;
class GameLevelsDataSource;

class MainGameBackgroundDataSource
{
public:
	MainGameBackgroundDataSource(void);
	~MainGameBackgroundDataSource(void);

	std::string getCurrentLevelBackground();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	GameLevelsDataSource *_gameLevelsDataSource;

};

