#include "GameTutorialsFactory.h"
#include "GameTutorialController.h"
#include "GameViewElementsKeys.h"
#include "StartLevelGameTutorial.h"
#include "GameTutorialOrderController.h"

using namespace std;
using namespace cocos2d;

GameTutorialsFactory::GameTutorialsFactory(GameTutorialController *aTutorialController)
{
	_gameTutorialController = aTutorialController;
	_gameTutorials = getTutorials();
}


GameTutorialsFactory::~GameTutorialsFactory(void)
{
}

map<string, function<GameTutorial*()> > GameTutorialsFactory::getTutorials()
{
	map<string, function<GameTutorial*()> > tutorials;

	tutorials[gameLevel1Key] = [this](){return new StartLevelGameTutorial(this);};
	tutorials[gameLevel2Key] = [this](){return new StartLevelGameTutorial(this);};
	tutorials[gameLevel4Key] = [this](){return new StartLevelGameTutorial(this);};

	return tutorials;
}

bool GameTutorialsFactory::availableTutorialForLevel(string aLevelKey)
{
	bool availableTutorial = false;
	map<string, function<GameTutorial*()> >::iterator tutorialsIterator = _gameTutorials.find(aLevelKey);
	if (tutorialsIterator != _gameTutorials.end())
	{
		availableTutorial = true;
	}
	return availableTutorial;
}

void GameTutorialsFactory::startTutorialForLevel(string aLevelKey)
{
	function<GameTutorial*()> tutorialFactory = _gameTutorials[aLevelKey];
	GameTutorial *currentTutorial = tutorialFactory();
	GameTutorialOrderController *gameTutorialOrderController = new GameTutorialOrderController(currentTutorial);
	this->addChild(gameTutorialOrderController);
	gameTutorialOrderController->startTutorial();
}

void GameTutorialsFactory::endTutorial()
{
	_gameTutorialController->endTutorial();
}