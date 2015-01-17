#pragma once

#include <string>

class CurrentPlayerDataSource;

class PlayerStatusDataSource
{
public:
	PlayerStatusDataSource(void);
	~PlayerStatusDataSource(void);

	std::string getPlayerName();
	std::string getPlayerScore();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;

};

