#pragma once

#include "GameTutorial.h"

class GameTutorialsFactory;

class StartLevelGameTutorial : public GameTutorial
{
public:
	StartLevelGameTutorial(GameTutorialsFactory *aDelegate);
	~StartLevelGameTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	int _allTutorialsCount;
	int _currentTutorialIndex;
	bool _availableTutorials;

};

