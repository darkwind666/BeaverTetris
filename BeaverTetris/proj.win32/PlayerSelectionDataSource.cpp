#include "PlayerSelectionDataSource.h"

PlayerSelectionDataSource::PlayerSelectionDataSource(void)
{
	int _selectedGameLevel = 0;
}


PlayerSelectionDataSource::~PlayerSelectionDataSource(void)
{
}

void PlayerSelectionDataSource::selectGameLevel(int aGameLevel)
{
	_selectedGameLevel = aGameLevel;
}

int PlayerSelectionDataSource::getSelectedGameLevel()
{
	return _selectedGameLevel;
}