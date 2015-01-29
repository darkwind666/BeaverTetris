#pragma once

#include "CurrentDetailControllerDelegate.h"
#include "cocos2d.h"

class CurrentDetailDataSource;

class CurrentDetailAnimationControler : public cocos2d::Node, public CurrentDetailControllerDelegate
{
public:
	CurrentDetailAnimationControler(void);
	~CurrentDetailAnimationControler(void);

	virtual void throwCurrentDetailOnPosition(GamePositionOnBoard aPosition);

private:

	CurrentDetailDataSource *_currentDetailDataSource;

};

