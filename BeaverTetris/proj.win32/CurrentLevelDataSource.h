#pragma once

#include "GameStructures.h"
#include "PlayerSelectionObserver.h"
#include "CurrentLevelDataSourceObserver.h"
#include <vector>

class CurrentLevelDataSource :public PlayerSelectionObserver
{
public:
	CurrentLevelDataSource(void);
	~CurrentLevelDataSource(void);

	GameLevelInformation getCurrentLevelData();
	void playerChangeSelectedLevel(int aCurrentSelectedLevel);

	void addObserver(CurrentLevelDataSourceObserver *aCurrentLevelDataSourceObserver);
	void removeObserver(CurrentLevelDataSourceObserver *aCurrentLevelDataSourceObserver);

private:

	std::vector<CurrentLevelDataSourceObserver*> _observers;

};

