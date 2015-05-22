#include "StartLevelGameTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;

StartLevelGameTutorial::StartLevelGameTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_currentTutorialIndex = 0;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
	_tutorials = getTutorials();
}


StartLevelGameTutorial::~StartLevelGameTutorial(void)
{
}

vector< function<FiniteTimeAction*()> > StartLevelGameTutorial::getTutorials()
{
	vector< function<FiniteTimeAction*()> > tutorials;

	tutorials.push_back([this](){return _tutorialsAnimationController->getPlayerControllsTutorial();});
	tutorials.push_back([this](){return _tutorialsAnimationController->getPlayerReduceLineTutorial();});
	tutorials.push_back([this](){return _tutorialsAnimationController->getPlayerControllsTutorial();});

	return tutorials;
}

void StartLevelGameTutorial::startTutorial()
{
	runCurrentTutorial();
}

void StartLevelGameTutorial::nextTutorial()
{
	if (_availableTutorials)
	{
		_tutorialsAnimationController->stopAllActions();
		_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
		_currentTutorialIndex++;
		showNextTutorial();
	}
}

void StartLevelGameTutorial::showNextTutorial()
{
	if (_currentTutorialIndex > (_tutorials.size() - 1))
	{
		_availableTutorials = false;
		_delegate->endTutorial();
	}
	else
	{
		runCurrentTutorial();
	}
}

void StartLevelGameTutorial::runCurrentTutorial()
{
	function<FiniteTimeAction*()> tutorialFactory = _tutorials[_currentTutorialIndex];
	FiniteTimeAction* tutorial = tutorialFactory();
	_tutorialsAnimationController->runAction(tutorial);
}

bool StartLevelGameTutorial::availableTutorials()
{
	return _availableTutorials;
}
