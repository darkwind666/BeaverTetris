#pragma once

#include "PlayerStatusDelegateInterface.h"
#include "cocos2d.h"
#include <vector>

class GameLevelsMenuDataSource;

class SelectGameLevelController : public cocos2d::Node, public PlayerStatusDelegateInterface
{
public:
	SelectGameLevelController(void);
	~SelectGameLevelController(void);

	virtual void showPlayerStatus();

private:

	GameLevelsMenuDataSource *_gameLevelsMenuDataSource;
	cocos2d::Menu* _menuView;

	void makeScrollableMenuWithBackground(cocos2d::Menu* aMenu);
	cocos2d::Node* makeScrollableMenuWithContent(cocos2d::Node* aContentContainer);

	std::vector<cocos2d::MenuItemImage*> makeLevelsIcons();
	void addLevelIconsToMenu(std::vector<cocos2d::MenuItemImage*>  aLevelIcons);
	cocos2d::Action* makeMenuAnimationWithIcons(std::vector<cocos2d::MenuItemImage*>  aLevelIcons);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> makeActionWithEachIcon(std::vector<cocos2d::MenuItemImage*>  aLevelIcons);

	void buttonWasPressed(cocos2d::Object* pSender);

};

