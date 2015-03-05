#pragma once

#include "cocos2d.h"
#include <vector>
#include <functional>

class SpellsViewDataSource;
class GameTimeStepController;

class PlayerSpellsControllerDesktop : public cocos2d::Node
{
public:
	PlayerSpellsControllerDesktop(void);
	~PlayerSpellsControllerDesktop(void);

	virtual void update(float delta);
	virtual void onEnterTransitionDidFinish();

	void keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent);

private:

	SpellsViewDataSource *_spellsViewDataSource;
	GameTimeStepController *_gameTimeStepController;
	std::vector<cocos2d::Sprite*> _spellsIcons;

	std::vector<cocos2d::Sprite*> makeSpellsIcons();
	std::vector<cocos2d::Node*> makeSpellsViewsWithIcons(std::vector<cocos2d::Sprite*> aIcons);
	cocos2d::Node* getSpellCostLabelWithIndex(int aSpellIndex);
	void addViewsToController(std::vector<cocos2d::Node*> aViews);
	void setUpKeyboard();
	int getViewIndexForKeyboardKey(int aKeyboardKey);
	void setColorInIconWithTexture(cocos2d::Node *aIcon, std::string aTexture);
	std::function<void()> getCallbackWithButtonIndex(int aButtonIndex);
};

