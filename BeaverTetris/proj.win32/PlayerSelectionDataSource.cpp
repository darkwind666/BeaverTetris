#include "PlayerSelectionDataSource.h"
#include "stdlib.h"

PlayerSelectionDataSource::PlayerSelectionDataSource(void)
{
	int _selectedGameLevel = 0;
	_playerSelectionObserver = NULL;
}


PlayerSelectionDataSource::~PlayerSelectionDataSource(void)
{
}

void PlayerSelectionDataSource::selectGameLevel(int aGameLevel)
{
	_selectedGameLevel = aGameLevel;

	if (_playerSelectionObserver)
	{
		_playerSelectionObserver->playerChangeSelectedLevel(aGameLevel);
	}

}

int PlayerSelectionDataSource::getSelectedGameLevel()
{
	return _selectedGameLevel;
}

void PlayerSelectionDataSource::addObserver(PlayerSelectionObserver *aPlayerSelectionObserver)
{
	_playerSelectionObserver = aPlayerSelectionObserver;
}

void PlayerSelectionDataSource::removeObserver(PlayerSelectionObserver *aPlayerSelectionObserver)
{
	if (_playerSelectionObserver == aPlayerSelectionObserver)
	{
		_playerSelectionObserver = NULL;
	}
}