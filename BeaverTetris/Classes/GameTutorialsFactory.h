#pragma once

#include "cocos2d.h"
#include <string>
#include <map>
#include <functional>

class GameTutorialController;
class GameTutorial;

class GameTutorialsFactory : public cocos2d::Node
{
public:
	GameTutorialsFactory(GameTutorialController *aTutorialController);
	~GameTutorialsFactory(void);

	bool availableTutorialForLevel(std::string aLevelKey);
	void startTutorialForLevel(std::string aLevelKey);
	void endTutorial();

private:

	GameTutorialController *_gameTutorialController;
	std::map< std::string, std::function<GameTutorial*()> > _gameTutorials;

	std::map< std::string, std::function<GameTutorial*()> > getTutorials();

};

