#pragma once

#include "cocos2d.h"
#include <functional>
#include <string>

class GameViewStyleHelper
{
public:
	GameViewStyleHelper(void);
	~GameViewStyleHelper(void);

	static void runStandardButtonActionWithCallback(cocos2d::Node *aButton, std::function<void()> aCallback);
	static void runButtonActionWithCallbackAndDuration(cocos2d::Node *aButton, std::function<void()> aCallback, float aDuration);
	static cocos2d::FiniteTimeAction* getSoundActionWithKey(std::string aKey);
	static cocos2d::LabelTTF* getStandardLabel();
	static cocos2d::Label* getStandardLabelWithFontSize(float aFontSize);
	static void addBackButtonToParentNodeWithKey(cocos2d::Node *aParentNode, std::string aKey);
	static void addBackButtonToParentNodeWithKeyAndCallback(cocos2d::Node *aParentNode, std::string aKey, cocos2d::ccMenuCallback aCallback);
	static void addBackButtonToParentNodeWithKeyAndCallbackAndLocalization(cocos2d::Node *aParentNode, std::string aKey, cocos2d::ccMenuCallback aCallback, std::string aLocale);
	static cocos2d::MenuItem* getCloseButtonWithKeyAndCallbackAndLocalization(std::string aKey, cocos2d::ccMenuCallback aCallback, std::string aLocale);
};

