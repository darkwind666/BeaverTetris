#include "StartLevelGameTutorial.h"
#include "GameTutorialsFactory.h"

StartLevelGameTutorial::StartLevelGameTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_allTutorialsCount = 3;
	_currentTutorialIndex = 0;
	_availableTutorials = true;
}


StartLevelGameTutorial::~StartLevelGameTutorial(void)
{
}

void StartLevelGameTutorial::startTutorial()
{
	_currentTutorialIndex++;
}

void StartLevelGameTutorial::nextTutorial()
{
	_currentTutorialIndex++;
	if (_currentTutorialIndex > _allTutorialsCount)
	{
		_availableTutorials = false;
		_delegate->endTutorial();
	}
}

bool StartLevelGameTutorial::availableTutorials()
{
	return _availableTutorials;
}
