#pragma once

#include "cocos2d.h"
#include "AddLineToBoardBottomSpellDelegate.h"

class AddLineToBoardSpellAnimationController : public AddLineToBoardBottomSpellDelegate, public cocos2d::Node
{
public:
	AddLineToBoardSpellAnimationController(void);
	~AddLineToBoardSpellAnimationController(void);

	virtual void addLineToGameBoard();

};

