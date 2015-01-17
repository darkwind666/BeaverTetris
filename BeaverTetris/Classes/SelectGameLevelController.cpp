#include "SelectGameLevelController.h"
#include "GameLevelsMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "CocosNodesHelper.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension; 
using namespace std;

SelectGameLevelController::SelectGameLevelController(void)
{
	_gameLevelsMenuDataSource = new GameLevelsMenuDataSource();
	vector<CCMenuItemImage*> levelsIcons = makeLevelsIcons();
	_menuView = makeScrollableMenuViewWithLevelIcons(levelsIcons);
	this->addChild(_menuView);
}


SelectGameLevelController::~SelectGameLevelController(void)
{

}

vector<CCMenuItemImage*> SelectGameLevelController::makeLevelsIcons()
{
	vector<CCMenuItemImage*> levelIcons;

	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount();
	
	for (int levelIndex = 0; levelIndex < availableLevelsCount; levelIndex++)
	{
		CCMenuItemImage *menuItem = CCMenuItemImage::create("HelloWorld.png","HelloWorld.png",CC_CALLBACK_1(SelectGameLevelController::buttonWasPressed, this));
		menuItem->setScaleX(0.1f);
		menuItem->setScaleY(0.2f);
		menuItem->setTag(levelIndex);
		menuItem->setPosition(_gameLevelsMenuDataSource->getLevelIconPositionForIndex(levelIndex));
		levelIcons.push_back(menuItem);
	}
	return levelIcons;
}

CCNode* SelectGameLevelController::makeScrollableMenuViewWithLevelIcons(vector<CCMenuItemImage*>  aLevelIcons)
{

	CCLayer *contentContainer = CCLayer::create();
	CCLayerColor *background = CCLayerColor::create(Color4B::BLUE);
	contentContainer->addChild(background);
	CCNode *levelsMenu = makeMenuViewWithLevelIcons(aLevelIcons);
	contentContainer->addChild(levelsMenu);

	CCNode *scrollableMenu = makeScrollableMenuWithContent(contentContainer);
	return scrollableMenu;
}

CCNode* SelectGameLevelController::makeMenuViewWithLevelIcons(vector<CCMenuItemImage*>  aLevelIcons)
{
	CCMenu *buttonMenu = CCMenu::create();
	buttonMenu->setPosition(Vec2(0,0));
	
	vector<CCMenuItemImage*>::iterator iconsIterator;
	
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		CCMenuItemImage *menuItem = *iconsIterator;
		buttonMenu->addChild(menuItem);
	}
	return buttonMenu;
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

void SelectGameLevelController::buttonWasPressed(CCObject* pSender)
{
	CCNode *button = (CCNode*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = [=](){CCLOG("%d", buttonTag);};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}