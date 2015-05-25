#include "FightWithBossLevelTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;


FightWithBossLevelTutorial::FightWithBossLevelTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
}


FightWithBossLevelTutorial::~FightWithBossLevelTutorial(void)
{
}

void FightWithBossLevelTutorial::startTutorial()
{
	FiniteTimeAction* tutorial = _tutorialsAnimationController->getPlayerFightWithBossTutorial();
	_tutorialsAnimationController->runAction(tutorial);
}

void FightWithBossLevelTutorial::nextTutorial()
{
	_tutorialsAnimationController->stopAllActions();
	_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
	_availableTutorials = false;
	_delegate->endTutorial();
}

bool FightWithBossLevelTutorial::availableTutorials()
{
	return _availableTutorials;
}