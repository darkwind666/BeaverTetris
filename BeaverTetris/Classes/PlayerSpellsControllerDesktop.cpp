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

const int spellRechargeViewTag = 1;

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

vector<Node*> PlayerSpellsControllerDesktop::makeSpellsIcons()
{
	vector<Node*> spellsIcons;
	int spellsCount = _spellsViewDataSource->getAvailableSpellsCount();
	for (int spellIndex = 0; spellIndex < spellsCount; spellIndex++)
	{
		Node *spellView = Node::create();
		setInSpellViewNormalIcon(spellView);
		setInSpellViewRechargedIcon(spellView);
		int spellKeyboardKey = _spellsViewDataSource->getPlayerSpellKeyboardKeyOnIndex(spellIndex);
		spellView->setTag(spellKeyboardKey);
		spellsIcons.push_back(spellView);
	}
	return spellsIcons;
}

void PlayerSpellsControllerDesktop::setInSpellViewNormalIcon(Node* aView)
{
	Sprite *spellIcon = Sprite::create("HelloWorld.png");
	spellIcon->setScaleY(0.08f);
	spellIcon->setScaleX(0.06f);
	spellIcon->setColor(ccColor3B::GREEN);
	aView->addChild(spellIcon);
}

void PlayerSpellsControllerDesktop::setInSpellViewRechargedIcon(Node* aView)
{
	Sprite *sourceView = Sprite::create("HelloWorld.png");
	sourceView->setColor(ccColor3B::RED);
	ProgressTimer *progress =  ProgressTimer::create(sourceView);
	progress->setPercentage(0);
	progress->setScaleY(0.08f);
	progress->setScaleX(0.06f);
	progress->setTag(spellRechargeViewTag);
	aView->addChild(progress);
}

vector<Node*> PlayerSpellsControllerDesktop::makeSpellsViewsWithIcons(vector<Node*> aIcons)
{
	vector<Node*> spellsViews;
	vector<Node*>::iterator iconsIterator;
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

void PlayerSpellsControllerDesktop::update(float delta)
{
	vector<Node*>::iterator iconsIterator;
	for (iconsIterator = _spellsIcons.begin(); iconsIterator != _spellsIcons.end(); iconsIterator++)
	{
		Node *spellIcon = *iconsIterator;
		int spellIndex = distance(_spellsIcons.begin(), iconsIterator);
		float spellRechargePercent = _spellsViewDataSource->getSpellRechargePercenOnIndex(spellIndex);
		ProgressTimer *spellRechargeView = (ProgressTimer*)spellIcon->getChildByTag(spellRechargeViewTag);
		spellRechargeView->setPercentage(spellRechargePercent);
	}
}

void PlayerSpellsControllerDesktop::keyPressed(cocos2d::EventKeyboard::KeyCode aKeyCode, cocos2d::Event *aEvent)
{
	int viewIndex = getViewIndexForKeyboardKey((int)aKeyCode);
	if (viewIndex >= 0 && _gameTimeStepController->getUpdataAvailable() == true)
	{
		_gameTimeStepController->setUpdateAvailable(false);
		Node* controllerView = _spellsIcons[viewIndex];
		function<void()> callback = getCallbackWithButtonIndex(viewIndex);
		GameViewStyleHelper::runStandardButtonActionWithCallback(controllerView ,callback);
	}
}

int PlayerSpellsControllerDesktop::getViewIndexForKeyboardKey(int aKeyboardKey)
{
	int viewIndex = -1;
	vector<Node*>::iterator iconsIterator;
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

function<void()> PlayerSpellsControllerDesktop::getCallbackWithButtonIndex(int aButtonIndex)
{
	function<void()> callback = [this, aButtonIndex](){
		_gameTimeStepController->setUpdateAvailable(true);
		_spellsViewDataSource->useSpellOnIndex(aButtonIndex);
	};
	return callback;
}