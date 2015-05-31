#pragma once

#include "GameTutorial.h"
#include <string>
#include <map>
#include <functional>

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class GameTutorialWithOneStep : public GameTutorial
{
public:
	GameTutorialWithOneStep(GameTutorialsFactory *aDelegate, std::string aKey);
	~GameTutorialWithOneStep(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	std::map< std::string, std::function<cocos2d::FiniteTimeAction*()> > _tutorialsFactories;
	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	bool _availableTutorials;
	std::string _tutorialKey;

	std::map< std::string, std::function<cocos2d::FiniteTimeAction*()> > getTutorialsFactories();

};

