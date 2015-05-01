#pragma once

#include "cocos2d.h"
#include "UIEditBox\UIEditBox.h"

class CurrentPlayerDataSource;
class PlayerStatusDelegateInterface;

class PlayerCreatorController : public cocos2d::Node, public cocos2d::ui::EditBoxDelegate
{
public:
	PlayerCreatorController(void);
	~PlayerCreatorController(void);

	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	virtual void onEnterTransitionDidFinish();

	void setDelegate(PlayerStatusDelegateInterface *aDelegate);

private:

	CurrentPlayerDataSource *_currentPlayerDataSource;
	cocos2d::Node *_controllerView;
	cocos2d::Vec2 _previousPosition;
	PlayerStatusDelegateInterface *_delegate;

	cocos2d::Node* getControllerView();
	cocos2d::Node* getPlayerCreatorText();
	cocos2d::Node* getPlayerCreatorInputHolder();
	cocos2d::MenuItem* getCloseButton();
	void invokeDelegate();

};

