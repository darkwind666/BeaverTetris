#pragma once

#include "ServiceInterface.h"
#include "GameEnums.h"

class GamePopUpsController : public ServiceInterface
{
public:

	GamePopUpsController(void);
	~GamePopUpsController(void);

	void showPopUp(PopUpType aPopUp);

};

