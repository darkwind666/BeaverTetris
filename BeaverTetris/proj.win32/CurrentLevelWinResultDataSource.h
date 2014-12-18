#pragma once

#include <string>

class CurrentLevelWinResultDataSource
{
public:
	CurrentLevelWinResultDataSource(void);
	~CurrentLevelWinResultDataSource(void);

	bool winGameResult();
	bool winAllGameResult();
	bool winCurrentGame(void);

	std::string getCurrentLevelName();
	int getCurrentLevelAward();

	void setCurrentGameWinResult(bool winResult);

};

