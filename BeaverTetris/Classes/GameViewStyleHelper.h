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

};

