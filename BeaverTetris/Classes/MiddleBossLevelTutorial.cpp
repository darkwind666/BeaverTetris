#include "MiddleBossLevelTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;

MiddleBossLevelTutorial::MiddleBossLevelTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
}


MiddleBossLevelTutorial::~MiddleBossLevelTutorial(void)
{
}

void MiddleBossLevelTutorial::startTutorial()
{
	FiniteTimeAction* tutorial = _tutorialsAnimationController->getPlayerUseFirestormSpellTutorial();
	_tutorialsAnimationController->runAction(tutorial);
}

void MiddleBossLevelTutorial::nextTutorial()
{
	_tutorialsAnimationController->stopAllActions();
	_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
	_availableTutorials = false;
	_delegate->endTutorial();
}

bool MiddleBossLevelTutorial::availableTutorials()
{
	return _availableTutorials;
}
