#pragma once

#include "GameTutorial.h"
#include <vector>
#include <functional>
#include <string>

class GameTutorialsFactory;
class GameTutorialsAnimationController;

class StartLevelGameTutorial : public GameTutorial
{
public:
	StartLevelGameTutorial(GameTutorialsFactory *aDelegate);
	~StartLevelGameTutorial(void);

	virtual void startTutorial();
	virtual void nextTutorial();
	virtual bool availableTutorials();

private:

	GameTutorialsFactory *_delegate;
	GameTutorialsAnimationController *_tutorialsAnimationController;
	int _currentTutorialIndex;
	bool _availableTutorials;
	std::vector< std::function<cocos2d::FiniteTimeAction*()> > _tutorials;

	std::vector< std::function<cocos2d::FiniteTimeAction*()> > getTutorials();
	cocos2d::FiniteTimeAction* getPlayerControllsTutorial();
	void showNextTutorial();
	void runCurrentTutorial();

};

