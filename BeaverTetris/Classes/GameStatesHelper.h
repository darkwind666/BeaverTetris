#pragma once

#include "GameEnums.h"

class GameStatesHelper
{
public:
	GameStatesHelper(void);
	~GameStatesHelper(void);

	static void goToScene(GameState aState);
	static void goToPopUp(PopUpType aPopUp);

};

