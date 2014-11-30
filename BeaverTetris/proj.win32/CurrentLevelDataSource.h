#pragma once

#include <string>

class CurrentLevelDataSource
{
public:
	CurrentLevelDataSource(void);
	~CurrentLevelDataSource(void);

	bool winGameResult();
	bool winAllGameResult();

	std::string getCurrentLevelName();
	int getCurrentLevelAward();

};

