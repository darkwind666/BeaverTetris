#pragma once

#include "cocos2d.h"
#include <functional>
#include "ui/CocosGUI.h"

class GameSoundEffectsRegulator : public cocos2d::Node
{
public:
	GameSoundEffectsRegulator(void);
	~GameSoundEffectsRegulator(void);

private:

	int getRegulatorPercent();
	std::function<void(cocos2d::Ref*,cocos2d::ui::Widget::TouchEventType)> getEventListnerForRegulator();

};

