#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"
#include <map>

class ScreenPopUp;

class GamePopUpsController : public ServiceInterface
{
public:

	GamePopUpsController(void);
	~GamePopUpsController(void);

	void showPopUp(PopUpType aPopUp);
	void subscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage);
	void unSubscribePupUpToMessage(ScreenPopUp *aPopUp, PopUpType aMessage);

private:

	std::map<PopUpType, ScreenPopUp*> _messageListnersPopUps;

};

