#include "EndLevelTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;

EndLevelTutorial::EndLevelTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
}


EndLevelTutorial::~EndLevelTutorial(void)
{
}

void EndLevelTutorial::startTutorial()
{
	FiniteTimeAction* tutorial = _tutorialsAnimationController->getPlayerUseCohesionSpellTutorial();
	_tutorialsAnimationController->runAction(tutorial);
}

void EndLevelTutorial::nextTutorial()
{
	_tutorialsAnimationController->stopAllActions();
	_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
	_availableTutorials = false;
	_delegate->endTutorial();
}

bool EndLevelTutorial::availableTutorials()
{
	return _availableTutorials;
}

