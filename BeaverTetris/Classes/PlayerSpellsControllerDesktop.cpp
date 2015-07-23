#include "PlayerSpellsControllerDesktop.h"
#include "SpellsViewDataSource.h"
#include "CocosNodesHelper.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "GameViewSuffixes.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"
#include "GameViewElementsKeys.h"
#include "StringsSupporter.h"

using namespace cocos2d;
using namespace std;

const int spellRechargeViewTag = 6;

PlayerSpellsControllerDesktop::PlayerSpellsControllerDesktop(void)
{
	_spellsViewDataSource = new SpellsViewDataSource();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_spellsIcons = makeSpellsIcons();
	vector<Node*> spellsViews = makeSpellsViewsWithIcons(_spellsIcons);
	addViewsToController(spellsViews);
}


PlayerSpellsControllerDesktop::~PlayerSpellsControllerDesktop(void)
{
	delete _spellsViewDataSource;
}

vector<MenuItem*> PlayerSpellsControllerDesktop::makeSpellsIcons()
{
	vector<MenuItem*> spellsIcons;
	int spellsCount = _spellsViewDataSource->getAvailableSpellsCount();
	for (int spellIndex = 0; spellIndex < spellsCount; spellIndex++)
	{
		string normalSpellImage = _spellsViewDataSource->getSpellIconImageOnIndex(spellIndex);
		Sprite *normalSpellView = Sprite::createWithSpriteFrameName(normalSpellImage);
		Sprite *selectedSpellView = Sprite::createWithSpriteFrameName(normalSpellImage);
		MenuItem *spellView = MenuItemSprite::create(normalSpellView, selectedSpellView, [this, spellIndex](Ref*){useSpellForIndex(spellIndex);});
		setInSpellViewRechargedIcon(spellView);
		int spellKeyboardKey = _spellsViewDataSource->getPlayerSpellKeyboardKeyOnIndex(spellIndex);
		spellView->setTag(spellKeyboardKey);
		spellsIcons.push_back(spellView);
	}
	return spellsIcons;
}

void PlayerSpellsControllerDesktop::setInSpellViewRechargedIcon(Node* aView)
{
	Sprite *sourceView = CocosNodesHelper::getSpriteWithKey(playerSpellImageKey);
	ProgressTimer *progress =  ProgressTimer::create(sourceView);
	progress->setReverseDirection(true);
	progress->setPercentage(0);
	progress->setTag(spellRechargeViewTag);
	Vec2 position = GameElementsDataHelper::getElementOffsetForKey(playerSpellImageKey);
	progress->setPosition(position);
	aView->addChild(progress);
}

vector<Node*> PlayerSpellsControllerDesktop::makeSpellsViewsWithIcons(vector<MenuItem*> aIcons)
{
	vector<Node*> spellsViews;
	vector<MenuItem*>::iterator iconsIterator;
	for (iconsIterator = aIcons.begin(); iconsIterator != aIcons.end(); iconsIterator++)
	{
		Menu *menuForIcon = Menu::createWithItem(*iconsIterator);

		int iconIndex = distance(aIcons.begin(), iconsIterator);
		Node *spellView = Node::create();
		Vec2 spellViewPosition = _spellsViewDataSource->getSpellPositionOnIndex(iconIndex);
		spellView->setPosition(spellViewPosition);

		Node *spellCostLabel = getSpellCostLabelWithIndex(iconIndex);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(menuForIcon, spellView, playerSpellImageKey);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(spellCostLabel, spellView, playerSpellCostLabelKey);
		spellsViews.push_back(spellView);
	}
	return spellsViews;
}

Node* PlayerSpellsControllerDesktop::getSpellCostLabelWithIndex(int aSpellIndex)
{
	Label *spellCostLabel = GameViewStyleHelper::getStandardLabelWithFontSize(16);
	string spellCost = _spellsViewDataSource->getSpellCostOnIndex(aSpellIndex);
	spellCostLabel->setString(spellCost);
	return spellCostLabel;
}

Node* PlayerSpellsControllerDesktop::getSpellButtonLabelWithIndex(int aSpellIndex)
{
	Label *spellButtonLabel = GameViewStyleHelper::getStandardLabelWithFontSize(13);
	spellButtonLabel->setColor(Color3B(41, 104, 110));
	string spellButtonName = StringsSupporter::getStringFromNumber(aSpellIndex + 1);
	spellButtonLabel->setString(spellButtonName);
	return spellButtonLabel;
}

void PlayerSpellsControllerDesktop::addViewsToController(vector<Node*> aViews)
{
	vector<Node*>::iterator viewsIterator;
	for (viewsIterator = aViews.begin(); viewsIterator != aViews.end(); viewsIterator++)
	{
		Node *view = *viewsIterator;
		this->addChild(view);
	}
}

void PlayerSpellsControllerDesktop::setUpKeyboard()
{
	EventListenerKeyboard *keyboardListner = EventListenerKeyboard::create();
	keyboardListner->onKeyPressed = CC_CALLBACK_2(PlayerSpellsControllerDesktop::keyPressed, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListner, this);
}

void PlayerSpellsControllerDesktop::update(float delta)
{
	vector<MenuItem*>::iterator iconsIterator;
	for (iconsIterator = _spellsIcons.begin(); iconsIterator != _spellsIcons.end(); iconsIterator++)
	{
		MenuItem *spellIcon = *iconsIterator;
		int spellIndex = distance(_spellsIcons.begin(), iconsIterator);
		float spellRechargePercent = _spellsViewDataSource->getSpellRechargePercenOnIndex(spellIndex);
		ProgressTimer *spellRechargeView = (ProgressTimer*)spellIcon->getChildByTag(spellRechargeViewTag);
		spellRechargeView->setPercentage(spellRechargePercent);
	}
}

void PlayerSpellsControllerDesktop::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	int viewIndex = getViewIndexForKeyboardKey((int)aKeyCode);
	if (viewIndex >= 0)
	{
		useSpellForIndex(viewIndex);
	}
}

int PlayerSpellsControllerDesktop::getViewIndexForKeyboardKey(int aKeyboardKey)
{
	int viewIndex = -1;
	vector<MenuItem*>::iterator iconsIterator;
	for (iconsIterator = _spellsIcons.begin(); iconsIterator != _spellsIcons.end(); iconsIterator++)
	{
		Node *spellIcon = *iconsIterator;
		if (spellIcon->getTag() == aKeyboardKey)
		{
			viewIndex = distance(_spellsIcons.begin(), iconsIterator);
			break;
		}
	}
	return viewIndex;
}

void PlayerSpellsControllerDesktop::useSpellForIndex(int aIndex)
{
	if (_gameTimeStepController->getUpdataAvailable() == true)
	{
		_gameTimeStepController->setUpdateAvailable(false);
		Node* controllerView = _spellsIcons[aIndex];
		function<void()> callback = getCallbackWithButtonIndex(aIndex);
		GameViewStyleHelper::runStandardButtonActionWithCallback(controllerView ,callback);
	}
}

function<void()> PlayerSpellsControllerDesktop::getCallbackWithButtonIndex(int aButtonIndex)
{
	function<void()> callback = [this, aButtonIndex](){
		_gameTimeStepController->setUpdateAvailable(true);
		_spellsViewDataSource->useSpellOnIndex(aButtonIndex);
	};
	return callback;
}