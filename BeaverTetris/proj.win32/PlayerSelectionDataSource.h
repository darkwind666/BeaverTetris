#pragma once
class PlayerSelectionDataSource
{
public:
	PlayerSelectionDataSource(void);
	~PlayerSelectionDataSource(void);

	void selectGameLevel(int aGameLevel);
	int getSelectedGameLevel();

private:

	int _selectedGameLevel;

};

