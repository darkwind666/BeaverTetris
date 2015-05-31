#include "FightWithBossLevelTutorial.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"

using namespace std;
using namespace cocos2d;


FightWithBossLevelTutorial::FightWithBossLevelTutorial(GameTutorialsFactory *aDelegate)
{
	_delegate = aDelegate;
	_currentTutorialIndex = 0;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
	_tutorials = getTutorials();
}


FightWithBossLevelTutorial::~FightWithBossLevelTutorial(void)
{
}

vector< function<FiniteTimeAction*()> > FightWithBossLevelTutorial::getTutorials()
{
	vector< function<FiniteTimeAction*()> > tutorials;

	tutorials.push_back([this](){return _tutorialsAnimationController->getPlayerFightWithBossTutorial();});
	tutorials.push_back([this](){return _tutorialsAnimationController->getPlayerUseRandomExplosionsSpellTutorial();});

	return tutorials;
}

void FightWithBossLevelTutorial::startTutorial()
{
	runCurrentTutorial();
}

void FightWithBossLevelTutorial::nextTutorial()
{
	if (_availableTutorials)
	{
		_tutorialsAnimationController->stopAllActions();
		_tutorialsAnimationController->removeAllChildrenWithCleanup(true);
		_currentTutorialIndex++;
		showNextTutorial();
	}
}

void FightWithBossLevelTutorial::showNextTutorial()
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

bool FightWithBossLevelTutorial::availableTutorials()
{
	return _availableTutorials;
}

void FightWithBossLevelTutorial::runCurrentTutorial()
{
	function<FiniteTimeAction*()> tutorialFactory = _tutorials[_currentTutorialIndex];
	FiniteTimeAction* tutorial = tutorialFactory();
	_tutorialsAnimationController->runAction(tutorial);
}