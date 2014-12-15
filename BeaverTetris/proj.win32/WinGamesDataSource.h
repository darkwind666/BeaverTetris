#pragma once
class WinGamesDataSource
{
public:
	WinGamesDataSource(void);
	~WinGamesDataSource(void);

	bool winAllGameResult();
	bool nextLevetAvailable();
	void goToNextLevel();

};

