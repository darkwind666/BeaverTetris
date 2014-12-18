#pragma once

#include "PlayerSelectionObserver.h"

class PlayerSelectionDataSource
{
public:
	PlayerSelectionDataSource(void);
	~PlayerSelectionDataSource(void);

	void selectGameLevel(int aGameLevel);
	int getSelectedGameLevel();

	void addObserver(PlayerSelectionObserver *aPlayerSelectionObserver);
	void removeObserver(PlayerSelectionObserver *aPlayerSelectionObserver);

private:

	int _selectedGameLevel;
	PlayerSelectionObserver *_playerSelectionObserver;

};

