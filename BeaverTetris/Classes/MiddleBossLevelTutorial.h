#pragma once

#include "GameTutorial.h"

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class MiddleBossLevelTutorial : public GameTutorial
{
public:
	MiddleBossLevelTutorial(GameTutorialsFactory *aDelegate);
	~MiddleBossLevelTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	bool _availableTutorials;

};

