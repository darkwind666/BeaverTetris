#pragma once

#include "GameTutorial.h"

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class EndLevelTutorial : public GameTutorial
{
public:
	EndLevelTutorial(GameTutorialsFactory *aDelegate);
	~EndLevelTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	bool _availableTutorials;

};

