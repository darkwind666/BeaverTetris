#include "SelectGameLevelController.h"
#include "GameLevelsMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "cocos-ext.h"
#include "GameAnimationActionsConstants.h"
#include "SelectGameLevelBackgroundController.h"

using namespace cocos2d;
using namespace cocos2d::extension; 
using namespace std;

SelectGameLevelController::SelectGameLevelController(void)
{
	_gameLevelsMenuDataSource = new GameLevelsMenuDataSource();
	vector<MenuItemImage*> levelsIcons = makeLevelsIcons();
	_menuView = Menu::create();
	_menuView->setPosition(Vec2(0,0));
	makeScrollableMenuWithBackground(_menuView);
}


SelectGameLevelController::~SelectGameLevelController(void)
{

}

void SelectGameLevelController::makeScrollableMenuWithBackground(Menu *aMenu)
{
	Layer *contentContainer = Layer::create();
	SelectGameLevelBackgroundController *selectGameLevelBackgroundController = new SelectGameLevelBackgroundController();
	contentContainer->addChild(selectGameLevelBackgroundController);
	contentContainer->addChild(aMenu);

	Node *scrollableMenu = makeScrollableMenuWithContent(contentContainer);
	this->addChild(scrollableMenu);
}


Node* SelectGameLevelController::makeScrollableMenuWithContent(Node* aContentContainer)
{
	Size winSise = Director::getInstance()->getWinSize();
	Size scrollSize = CCSizeMake(winSise.width, winSise.height + 360);
	ScrollView *scrollLayer = ScrollView::create(winSise, aContentContainer);
	scrollLayer->ignoreAnchorPointForPosition(false);
	scrollLayer->setDirection(ScrollView::Direction::VERTICAL);
	scrollLayer->setContentSize(scrollSize);
	scrollLayer->setBounceable(false);
	return scrollLayer;
}

void SelectGameLevelController::showPlayerStatus()
{
	vector<MenuItemImage*> levelIcons = makeLevelsIcons();
	addLevelIconsToMenu(levelIcons);
	Action *menuAnimation = makeMenuAnimationWithIcons(levelIcons);
	this->runAction(menuAnimation);
}

vector<MenuItemImage*> SelectGameLevelController::makeLevelsIcons()
{
	vector<MenuItemImage*> levelIcons;

	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount();
	for (int levelIndex = 0; levelIndex < availableLevelsCount; levelIndex++)
	{
		MenuItemImage *menuItem = MenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(SelectGameLevelController::buttonWasPressed, this));
		menuItem->setScale(0.0f);
		menuItem->setTag(levelIndex);
		menuItem->setPosition(_gameLevelsMenuDataSource->getLevelIconPositionForIndex(levelIndex));
		levelIcons.push_back(menuItem);
	}
	return levelIcons;
}

void SelectGameLevelController::addLevelIconsToMenu(vector<MenuItemImage*>  aLevelIcons)
{
	vector<MenuItemImage*>::iterator iconsIterator;
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		MenuItemImage *menuItem = *iconsIterator;
		_menuView->addChild(menuItem);
	}
}

Action*  SelectGameLevelController::makeMenuAnimationWithIcons(vector<MenuItemImage*>  aLevelIcons)
{
	Vector<FiniteTimeAction*> actions = makeActionWithEachIcon(aLevelIcons);
	Action *sequence = Sequence::create(actions);
	return sequence;
}

Vector<FiniteTimeAction*> SelectGameLevelController::makeActionWithEachIcon(vector<MenuItemImage*>  aLevelIcons)
{
	Vector<FiniteTimeAction*> actions;
	vector<MenuItemImage*>::iterator iconsIterator;
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		Node *menuItem = *iconsIterator;
		FiniteTimeAction *scaleUp = ScaleTo::create(levelIconAppearActionDuration, 0.1f, 0.2f);
		FiniteTimeAction *actionWithLevelIcon = TargetedAction::create(menuItem, scaleUp);
		actions.pushBack(actionWithLevelIcon);
	}
	return actions;
}

void SelectGameLevelController::buttonWasPressed(Object* pSender)
{
	Node *button = (Node*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = [=](){_gameLevelsMenuDataSource->selectGameLevelForIndex(buttonTag);};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}