#pragma once

#include <string>

class CurrentLevelWinResultDataSource
{
public:
	CurrentLevelWinResultDataSource(void);
	~CurrentLevelWinResultDataSource(void);

	bool winGameResult();
	bool winAllGameResult();

	std::string getCurrentLevelName();
	int getCurrentLevelAward();

};

