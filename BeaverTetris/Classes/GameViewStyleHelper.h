#pragma once

#include "cocos2d.h"
#include <functional>

class GameViewStyleHelper
{
public:
	GameViewStyleHelper(void);
	~GameViewStyleHelper(void);

	static void runStandardButtonActionWithCallback(cocos2d::CCNode *aButton, std::function<void()> aCallback);
	static void runButtonActionWithCallbackAndDuration(cocos2d::CCNode *aButton, std::function<void()> aCallback, float aDuration);
	static cocos2d::LabelTTF* getStandardLabel();

};

