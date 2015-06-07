#include "GameTutorialWithOneStep.h"
#include "GameTutorialsFactory.h"
#include "GameTutorialsAnimationController.h"
#include "GameViewElementsKeys.h"

using namespace std;
using namespace cocos2d;

GameTutorialWithOneStep::GameTutorialWithOneStep(GameTutorialsFactory *aDelegate, string aKey)
{
	_delegate = aDelegate;
	_tutorialKey = aKey;
	_availableTutorials = true;
	GameTutorialsAnimationController *tutorialsAnimationController = new GameTutorialsAnimationController();
	_tutorialsAnimationController = tutorialsAnimationController;
	this->addChild(tutorialsAnimationController);
	_tutorialsFactories = getTutorialsFactories();

}


GameTutorialWithOneStep::~GameTutorialWithOneStep(void)
{
}

map< string, function<FiniteTimeAction*()> > GameTutorialWithOneStep::getTutorialsFactories()
{
	map< string, function<FiniteTimeAction*()> > tutorialsFactories;

	tutorialsFactories[gameLevel2Key] = [this](){return _tutorialsAnimationController->getPlayerUseRocketSpellTutorial();};
	tutorialsFactories[gameLevel7Key] = [this](){return _tutorialsAnimationController->getPlayerUseFirestormSpellTutorial();};
	tutorialsFactories[gameLevel9Key] = [this](){return _tutorialsAnimationController->getPlayerUseCohesionSpellTutorial();};

	return tutorialsFactories;
}

void GameTutorialWithOneStep::startTutorial()
{
	function<FiniteTimeAction*()> tutorialsFactory = _tutorialsFactories[_tutorialKey];
	FiniteTimeAction* tutorial = tutorialsFactory();
	_tutorialsAnimationController->runAction(tutorial);
}

void GameTutorialWithOneStep::nextTutorial()
{
	_tutorialsAnimationController->cleanCurrentTutorial();
	_availableTutorials = false;
	_delegate->endTutorial();
}

bool GameTutorialWithOneStep::availableTutorials()
{
	return _availableTutorials;
}
