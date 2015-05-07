#pragma once

#include "ServiceInterface.h"
#include <string>
#include "GameEnums.h"

class GoogleAnalyticIndicatorsDataSource;

class GameAnalyticController : public ServiceInterface
{
public:
	GameAnalyticController(void);
	~GameAnalyticController(void);

	void createdNewPlayerWithName(std::string aName);
	void winAllGameWithResult(int aResult);
	void winSelectedLevel();
	void loseSelectedLevel();
	void useSpell(std::string aSpellKey);
	void goToPopUp(PopUpType aPopUp);
	void goToScreen(GameState aScreen);

private:

	GoogleAnalyticIndicatorsDataSource *_indicatorsNamesDataSource;

	void endGame();

};

