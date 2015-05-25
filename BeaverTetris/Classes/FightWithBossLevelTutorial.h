#pragma once

#include "GameTutorial.h"

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class FightWithBossLevelTutorial : public GameTutorial
{
public:
	FightWithBossLevelTutorial(GameTutorialsFactory *aDelegate);
	~FightWithBossLevelTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	bool _availableTutorials;

};

