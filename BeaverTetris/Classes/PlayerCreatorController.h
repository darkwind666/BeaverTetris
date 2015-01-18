#pragma once

#include "cocos2d.h"
#include "UIEditBox\UIEditBox.h"

class CurrentPlayerDataSource;

class PlayerCreatorController : public cocos2d::Node, public cocos2d::ui::EditBoxDelegate
{
public:
	PlayerCreatorController(void);
	~PlayerCreatorController(void);

	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	cocos2d::Node *_controllerView;
	cocos2d::Vec2 _previousPosition;

	cocos2d::Node* getControllerView();
	cocos2d::Node* getPlayerCreatorPad();
	cocos2d::Node* getPlayerCreatorText();
	cocos2d::Node* getPlayerCreatorInputHolder();

};

