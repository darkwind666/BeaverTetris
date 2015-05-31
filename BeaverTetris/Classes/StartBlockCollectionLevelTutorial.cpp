#include "StartBlockCollectionLevelTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;

StartBlockCollectionLevelTutorial::StartBlockCollectionLevelTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
}


StartBlockCollectionLevelTutorial::~StartBlockCollectionLevelTutorial(void)
{
}

void StartBlockCollectionLevelTutorial::startTutorial()
{
	FiniteTimeAction* tutorial = _tutorialsAnimationController->getPlayerUseRocketSpellTutorial();
	_tutorialsAnimationController->runAction(tutorial);
}

void StartBlockCollectionLevelTutorial::nextTutorial()
{
	_tutorialsAnimationController->stopAllActions();
	_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
	_availableTutorials = false;
	_delegate->endTutorial();
}

bool StartBlockCollectionLevelTutorial::availableTutorials()
{
	return _availableTutorials;
}

