#include "PlayerSpellsControllerDesktop.h"
#include "SpellsViewDataSource.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "GameViewSuffixes.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameTimeStepController.h"

using namespace cocos2d;
using namespace std;

PlayerSpellsControllerDesktop::PlayerSpellsControllerDesktop(void)
{
	_spellsViewDataSource = new SpellsViewDataSource();
	_gameTimeStepController = (GameTimeStepController*)ServiceLocator::getServiceForKey(gameTimeStepControllerKey);
	_spellsIcons = makeSpellsIcons();
	vector<Node*> spellsViews = makeSpellsViewsWithIcons(_spellsIcons);
	addViewsToController(spellsViews);
	setUpKeyboard();
}


PlayerSpellsControllerDesktop::~PlayerSpellsControllerDesktop(void)
{
	delete _spellsViewDataSource;
}

vector<Sprite*> PlayerSpellsControllerDesktop::makeSpellsIcons()
{
	vector<Sprite*> spellsIcons;
	int spellsCount = _spellsViewDataSource->getAvailableSpellsCount();
	for (int spellIndex = 0; spellIndex < spellsCount; spellIndex++)
	{
		Sprite *spellIcon = Sprite::create("HelloWorld.png");
	    spellIcon->setScaleY(0.08f);
		spellIcon->setScaleX(0.06f);
		int spellKeyboardKey = _spellsViewDataSource->getPlayerSpellKeyboardKeyOnIndex(spellIndex);
		spellIcon->setTag(spellKeyboardKey);
		spellsIcons.push_back(spellIcon);
	}
	return spellsIcons;
}

vector<Node*> PlayerSpellsControllerDesktop::makeSpellsViewsWithIcons(vector<Sprite*> aIcons)
{
	vector<Node*> spellsViews;
	vector<Sprite*>::iterator iconsIterator;
	for (iconsIterator = aIcons.begin(); iconsIterator != aIcons.end(); iconsIterator++)
	{
		int iconIndex = distance(aIcons.begin(), iconsIterator);
		Node *spellView = Node::create();
		Vec2 spellViewPosition = _spellsViewDataSource->getSpellPositionOnIndex(iconIndex);
		spellView->setPosition(spellViewPosition);
		Node *spellCostLabel = getSpellCostLabelWithIndex(iconIndex);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(*iconsIterator, spellView, playerSpellImageKey);
		CocosNodesHelper::addChildNodeToParentNodeWithKey(spellCostLabel, spellView, playerSpellCostLabelKey);
		spellsViews.push_back(spellView);
	}
	return spellsViews;
}

Node* PlayerSpellsControllerDesktop::getSpellCostLabelWithIndex(int aSpellIndex)
{
	LabelTTF *spellCostLabel = GameViewStyleHelper::getStandardLabel();
	spellCostLabel->setFontSize(20);
	string spellCost = _spellsViewDataSource->getSpellCostOnIndex(aSpellIndex);
	spellCostLabel->setString(spellCost);
	return spellCostLabel;
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

void PlayerSpellsControllerDesktop::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	int viewIndex = getViewIndexForKeyboardKey((int)aKeyCode);
	if (viewIndex >= 0 && _gameTimeStepController->getUpdataAvailable() == true)
	{
		Node* controllerView = _spellsIcons[viewIndex];
		function<void()> callback = [this, viewIndex](){_spellsViewDataSource->useSpellOnIndex(viewIndex);};
		GameViewStyleHelper::runStandardButtonActionWithCallback(controllerView ,callback);
	}
}

int PlayerSpellsControllerDesktop::getViewIndexForKeyboardKey(int aKeyboardKey)
{
	int viewIndex = -1;
	vector<Sprite*>::iterator iconsIterator;
	for (iconsIterator = _spellsIcons.begin(); iconsIterator != _spellsIcons.end(); iconsIterator++)
	{
		Sprite *spellIcon = *iconsIterator;
		if (spellIcon->getTag() == aKeyboardKey)
		{
			viewIndex = distance(_spellsIcons.begin(), iconsIterator);
			break;
		}
	}
	return viewIndex;
}

void PlayerSpellsControllerDesktop::update(float delta)
{
	vector<Sprite*>::iterator iconsIterator;
	for (iconsIterator = _spellsIcons.begin(); iconsIterator != _spellsIcons.end(); iconsIterator++)
	{
		Sprite *spellIcon = *iconsIterator;
		int spellIndex = distance(_spellsIcons.begin(), iconsIterator);
		string spellIconTexture = _spellsViewDataSource->getSpellIconImageOnIndex(spellIndex);
		setColorInIconWithTexture(spellIcon, spellIconTexture);
	}
}

void PlayerSpellsControllerDesktop::setColorInIconWithTexture(Node* aIcon, string aTexture)
{
	int fileExtensionPosition = aTexture.find(lockedPrefix);
	if (fileExtensionPosition >= 0)
	{
		aIcon->setColor(ccColor3B::RED);
	}
	else
	{
		aIcon->setColor(ccColor3B::GREEN);
	}
}

void PlayerSpellsControllerDesktop::onEnterTransitionDidFinish()
{
	this->scheduleUpdate();
}