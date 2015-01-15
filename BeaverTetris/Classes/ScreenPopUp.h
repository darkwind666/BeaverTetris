#pragma once

#include "GameEnums.h"

class ScreenPopUp
{
public:
	ScreenPopUp(void);
	virtual ~ScreenPopUp(void);

	virtual void showPopUp() = 0;
	virtual void closePopUp() = 0;

	void subscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage);
	void unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage);

};


