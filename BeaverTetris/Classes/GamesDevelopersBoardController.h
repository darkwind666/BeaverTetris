#pragma once

#include "cocos2d.h"
#include <string>

class GamesDevelopersBoardController : public cocos2d::Node
{
public:
	GamesDevelopersBoardController(void);
	~GamesDevelopersBoardController(void);

private:

	void makeBoardView();
	void makeViewWithPadAndFunctionAndNameKeys(std::string aPadKey, std::string aFunctionKey, std::string aNameKey);
	cocos2d::Node* getDeveloperPadWithKey(std::string aPadKey);
	cocos2d::Node* getDeveloperLabelWithString(std::string aString);
	void createBackToMainMenuButton();
	cocos2d::MenuItem* getCloseButton();
};

