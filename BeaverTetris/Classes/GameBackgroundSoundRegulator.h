#pragma once

#include "cocos2d.h"
#include <functional>
#include "ui/CocosGUI.h"

class GameBackgroundSoundRegulator : public cocos2d::CCNode
{
public:
	GameBackgroundSoundRegulator(void);
	~GameBackgroundSoundRegulator(void);

private:

	int getRegulatorPercent();
	std::function<void(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType)> getEventListnerForRegulator();

};

