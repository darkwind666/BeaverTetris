#pragma once

#include "GameTutorial.h"

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class StartBlockCollectionLevelTutorial : public GameTutorial
{
public:
	StartBlockCollectionLevelTutorial(GameTutorialsFactory *aDelegate);
	~StartBlockCollectionLevelTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	bool _availableTutorials;

};

