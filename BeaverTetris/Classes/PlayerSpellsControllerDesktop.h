#pragma once

#include "cocos2d.h"

class PlayerSpellsControllerDesktop : public cocos2d::Node
{
public:
	PlayerSpellsControllerDesktop(void);
	~PlayerSpellsControllerDesktop(void);

	virtual void update(float delta);
	virtual void onEnterTransitionDidFinish();

};

