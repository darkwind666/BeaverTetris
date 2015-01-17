#include "SelectGameLevelController.h"
#include "GameLevelsMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "cocos-ext.h"
#include "GameAnimationActionsConstants.h"

using namespace cocos2d;
using namespace cocos2d::extension; 
using namespace std;

SelectGameLevelController::SelectGameLevelController(void)
{
	_gameLevelsMenuDataSource = new GameLevelsMenuDataSource();
	vector<CCMenuItemImage*> levelsIcons = makeLevelsIcons();
	_menuView = CCMenu::create();
	_menuView->setPosition(Vec2(0,0));
	makeScrollableMenuWithBackground(_menuView);
}


SelectGameLevelController::~SelectGameLevelController(void)
{

}

void SelectGameLevelController::makeScrollableMenuWithBackground(CCMenu *aMenu)
{

	CCLayer *contentContainer = CCLayer::create();
	CCLayerColor *background = CCLayerColor::create(Color4B::BLUE);
	contentContainer->addChild(background);
	contentContainer->addChild(aMenu);

	CCNode *scrollableMenu = makeScrollableMenuWithContent(contentContainer);
	this->addChild(scrollableMenu);
}


CCNode* SelectGameLevelController::makeScrollableMenuWithContent(CCNode* aContentContainer)
{
	Size winSise = CCDirector::getInstance()->getWinSize();
	Size scrollSize = CCSizeMake(winSise.width, winSise.height + 360);
	ScrollView *scrollLayer = ScrollView::create(winSise, aContentContainer);
	scrollLayer->ignoreAnchorPointForPosition(false);
	scrollLayer->setDirection(ScrollView::Direction::VERTICAL);
	scrollLayer->setContentSize(scrollSize);
	scrollLayer->setBounceable(false);
	return scrollLayer;
}

void SelectGameLevelController::onEnterTransitionDidFinish()
{
	vector<CCMenuItemImage*> levelIcons = makeLevelsIcons();
	addLevelIconsToMenu(levelIcons);
	CCAction *menuAnimation = makeMenuAnimationWithIcons(levelIcons);
	this->runAction(menuAnimation);
}

vector<CCMenuItemImage*> SelectGameLevelController::makeLevelsIcons()
{
	vector<CCMenuItemImage*> levelIcons;

	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount();
	for (int levelIndex = 0; levelIndex < availableLevelsCount; levelIndex++)
	{
		CCMenuItemImage *menuItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(SelectGameLevelController::buttonWasPressed, this));
		menuItem->setScale(0.0f);
		menuItem->setTag(levelIndex);
		menuItem->setPosition(_gameLevelsMenuDataSource->getLevelIconPositionForIndex(levelIndex));
		levelIcons.push_back(menuItem);
	}
	return levelIcons;
}

void SelectGameLevelController::addLevelIconsToMenu(vector<CCMenuItemImage*>  aLevelIcons)
{
	vector<CCMenuItemImage*>::iterator iconsIterator;
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		CCMenuItemImage *menuItem = *iconsIterator;
		_menuView->addChild(menuItem);
	}
}

CCAction*  SelectGameLevelController::makeMenuAnimationWithIcons(vector<CCMenuItemImage*>  aLevelIcons)
{
	Vector<FiniteTimeAction*> actions = makeActionWithEachIcon(aLevelIcons);
	CCAction *sequence = CCSequence::create(actions);
	return sequence;
}

Vector<FiniteTimeAction*> SelectGameLevelController::makeActionWithEachIcon(vector<CCMenuItemImage*>  aLevelIcons)
{
	Vector<FiniteTimeAction*> actions;
	vector<CCMenuItemImage*>::iterator iconsIterator;
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		CCNode *menuItem = *iconsIterator;
		CCFiniteTimeAction *scaleUp = CCScaleTo::create(levelIconAppearActionDuration, 0.1f, 0.2f);
		CCFiniteTimeAction *actionWithLevelIcon = CCTargetedAction::create(menuItem, scaleUp);
		actions.pushBack(actionWithLevelIcon);
	}
	return actions;
}

void SelectGameLevelController::buttonWasPressed(CCObject* pSender)
{
	CCNode *button = (CCNode*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = [=](){CCLOG("%d", buttonTag);};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}