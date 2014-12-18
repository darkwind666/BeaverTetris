#pragma once
class PlayerSelectionObserver
{
public:
	PlayerSelectionObserver(void);
	~PlayerSelectionObserver(void);

	virtual void playerChangeSelectedLevel(int aCurrentSelectedLevel) = 0;

};


