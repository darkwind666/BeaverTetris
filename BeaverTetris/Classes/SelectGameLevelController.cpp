#include "SelectGameLevelController.h"
#include "GameLevelsMenuDataSource.h"
#include "GameViewStyleHelper.h"
#include "cocos-ext.h"
#include "GameAnimationActionsConstants.h"
#include "SelectGameLevelBackgroundController.h"
#include "SelectGameLevelBeaverOnRaftController.h"

using namespace cocos2d;
using namespace cocos2d::extension; 
using namespace std;

SelectGameLevelController::SelectGameLevelController(void)
{
	_gameLevelsMenuDataSource = new GameLevelsMenuDataSource();
	_menuView = Menu::create();
	_menuView->setPosition(Vec2(0,0));
	vector<MenuItem*> levelIcons = makeLevelsIcons();
	addLevelIconsToMenu(levelIcons);
	makeScrollableMenuWithBackground(_menuView);
	_delegate = NULL;
}


SelectGameLevelController::~SelectGameLevelController(void)
{

}

void SelectGameLevelController::makeScrollableMenuWithBackground(Menu *aMenu)
{
	Layer *contentContainer = Layer::create();
	SelectGameLevelBackgroundController *selectGameLevelBackgroundController = new SelectGameLevelBackgroundController();
	vector<Node*> completedLevelsSigns = getCompletedLevelsSigns();
	SelectGameLevelBeaverOnRaftController *beaverOnRaftController = new SelectGameLevelBeaverOnRaftController();
	contentContainer->addChild(selectGameLevelBackgroundController);
	contentContainer->addChild(aMenu);
	addCompletedLevelSignsToBackground(completedLevelsSigns, contentContainer);
	contentContainer->addChild(beaverOnRaftController);
	Node *scrollableMenu = makeScrollableMenuWithContent(contentContainer);
	this->addChild(scrollableMenu);
}

vector<Node*> SelectGameLevelController::getCompletedLevelsSigns()
{
	vector<Node*> completedLevelsSigns;
	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount();
	for (int levelIndex = 0; levelIndex < availableLevelsCount; levelIndex++)
	{
		if (_gameLevelsMenuDataSource->levelCompletedForIndex(levelIndex))
		{
			Sprite *completedLevelsSignImage = Sprite::createWithSpriteFrameName(_gameLevelsMenuDataSource->getCompletedLevelSignImage());
			completedLevelsSignImage->setPosition(_gameLevelsMenuDataSource->getLevelCompletedSignPositionForIndex(levelIndex));
			completedLevelsSigns.push_back(completedLevelsSignImage);
		}
	}
	return completedLevelsSigns;
}

void SelectGameLevelController::addCompletedLevelSignsToBackground(vector<Node*> &aCompletedLevelsSigns, Node *aBackground)
{
	vector<Node*>::iterator signsIterator;
	for (signsIterator = aCompletedLevelsSigns.begin(); signsIterator != aCompletedLevelsSigns.end(); signsIterator++)
	{
		Node *levelSign = *signsIterator;
		aBackground->addChild(levelSign);
	}
}


Node* SelectGameLevelController::makeScrollableMenuWithContent(Node* aContentContainer)
{
	Size winSise = Director::getInstance()->getWinSize();
	Size scrollSize = CCSizeMake(winSise.width, winSise.height + 50);
	ScrollView *scrollLayer = ScrollView::create(winSise, aContentContainer);
	scrollLayer->ignoreAnchorPointForPosition(false);
	scrollLayer->setDirection(ScrollView::Direction::VERTICAL);
	scrollLayer->setContentSize(scrollSize);
	scrollLayer->setBounceable(false);
	return scrollLayer;
}

vector<MenuItem*> SelectGameLevelController::makeLevelsIcons()
{
	vector<MenuItem*> levelIcons;
	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount() - 1;
	for (int levelIndex = 0; levelIndex < availableLevelsCount; levelIndex++)
	{
		MenuItem *levelIconButton = getIconForIndex(levelIndex);
		levelIcons.push_back(levelIconButton);
	}
	return levelIcons;
}

cocos2d::MenuItem* SelectGameLevelController::getIconForIndex(int aIndex)
{
	string imageName = _gameLevelsMenuDataSource->getLevelIconImageForIndex(aIndex);
	Sprite *activeImage = Sprite::createWithSpriteFrameName(imageName);
	Sprite *inactiveImage = Sprite::createWithSpriteFrameName(imageName);
	MenuItemSprite *levelIconButton = MenuItemSprite::create(activeImage, inactiveImage, CC_CALLBACK_1(SelectGameLevelController::buttonWasPressed, this));
	levelIconButton->setTag(aIndex);
	levelIconButton->setPosition(_gameLevelsMenuDataSource->getLevelIconPositionForIndex(aIndex));
	return levelIconButton;
}

void SelectGameLevelController::addLevelIconsToMenu(vector<MenuItem*>  aLevelIcons)
{
	vector<MenuItem*>::iterator iconsIterator;
	for (iconsIterator = aLevelIcons.begin(); iconsIterator != aLevelIcons.end(); iconsIterator++)
	{
		MenuItem *menuItem = *iconsIterator;
		_menuView->addChild(menuItem);
	}
}

void SelectGameLevelController::showPlayerStatus()
{
	MenuItem* levelIcon = makeAvailableLevelIcon();
	_menuView->addChild(levelIcon);
	FiniteTimeAction *menuAnimation = makeMenuAnimationWithAvailableLevelIcon(levelIcon);
	FiniteTimeAction *invokeDelegateAction = getDelegateAction();
	Action *sequence = Sequence::create(menuAnimation, invokeDelegateAction, NULL);
	this->runAction(sequence);
}

MenuItem* SelectGameLevelController::makeAvailableLevelIcon()
{
	int availableLevelsCount = _gameLevelsMenuDataSource->getLevelsCount() - 1;
	MenuItem* levelIcon = getIconForIndex(availableLevelsCount);
	levelIcon->setScale(0.0f);
	return levelIcon;
}

FiniteTimeAction*  SelectGameLevelController::makeMenuAnimationWithAvailableLevelIcon(MenuItem *aLevelIcon)
{
	FiniteTimeAction *scaleUp = ScaleTo::create(levelIconAppearActionDuration, 1.0f);
	FiniteTimeAction *actionWithLevelIcon = TargetedAction::create(aLevelIcon, scaleUp);
	return actionWithLevelIcon;
}

FiniteTimeAction* SelectGameLevelController::getDelegateAction()
{
	FiniteTimeAction *delegateAction = CCCallFunc::create([this](){
		if (_delegate)
		{
			_delegate->showPlayerStatus();
		}
	});
	return delegateAction;
}

void SelectGameLevelController::buttonWasPressed(Object* pSender)
{
	Node *button = (Node*)pSender;
	int buttonTag = button->getTag();
	std::function<void()> buttonCallback = [=](){_gameLevelsMenuDataSource->selectGameLevelForIndex(buttonTag);};
	GameViewStyleHelper::runStandardButtonActionWithCallback(button, buttonCallback);
}

void SelectGameLevelController::setDelegate(PlayerStatusDelegateInterface *aDelegate)
{
	_delegate = aDelegate;
}