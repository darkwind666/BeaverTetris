#pragma once

#include "ServiceInterface.h"

class CurrentPlayerDataSource;

class StartMainGamePlayerScoreDataSource : public ServiceInterface
{
public:
	StartMainGamePlayerScoreDataSource(void);
	~StartMainGamePlayerScoreDataSource(void);

	void restorePlayerScore();

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	int _startGamePlayerScore;

};

