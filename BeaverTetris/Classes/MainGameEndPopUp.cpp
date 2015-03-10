#include "MainGameEndPopUp.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"

#include "GameElementsDataHelper.h"
#include "GameViewStyleHelper.h"
#include "GameAnimationActionsConstants.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include <vector>
#include "EndGameMenuElementsFactory.h"

using namespace cocos2d;
using namespace std;

MainGameEndPopUp::MainGameEndPopUp(void)
{
	ScreenPopUp::subscribePopUpToMessage(this, kEndGamePopUp);
	_popUpView = makePopUpView();
}
p

MainGameEndPopUp::~MainGameEndPopUp(void)
{
	ScreenPopUp::unSubscribePupUpToMessage(this, kEndGamePopUp);
}

CCNode* MainGameEndPopUp::makePopUpView()
{
	CCLayerColor *popUpPad = CCLayerColor::create(Color4B::RED, 300, 200);
	popUpPad->ignoreAnchorPointForPosition(false);
	CocosNodesHelper::addChildNodeToParentNodeWithKey(popUpPad,this,mainGameEndPopUpPadKey);
	return popUpPad;
}

void MainGameEndPopUp::showPopUp()
{
	fillViewWithElements();
	Vec2 newControllerPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(mainGameEndPopUpPadKey);
	CCActionInterval *moveController = CCMoveTo::create(regulateSoundPopUpStartAppearDuration, newControllerPosition);
	Action *ease = CCEaseBackOut::create(moveController);
	_popUpView->runAction(ease);
}

void MainGameEndPopUp::fillViewWithElements()
{
	EndGameMenuElementsFactory endGameMenuElementsFactory;
	vector<Node*> endGameViewElements = endGameMenuElementsFactory.getEndGameViewElements();
	vector<Node*>::iterator elementsIterator;
	for (elementsIterator = endGameViewElements.begin(); elementsIterator != endGameViewElements.end(); elementsIterator++)
	{
		Node *viewElement = *elementsIterator;
		int elementIndex = distance(endGameViewElements.begin(), elementsIterator);
		Vec2 elementPosition = getElementPositionForIndex(elementIndex);
		viewElement->setPosition(elementPosition);
		_popUpView->addChild(viewElement);
	}
}

Vec2 MainGameEndPopUp::getElementPositionForIndex(int aIndex)
{
	GameViewElementsDataSource *viewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 startElementPosition = viewElementsDataSource->getElementPositionForKey(mainGameEndPopUpButtonKey);
	Vec2 offset = viewElementsDataSource->getElementOffsetForKey(mainGameEndPopUpButtonKey);
	Vec2 elementPosition = Vec2(startElementPosition.x, startElementPosition.y + offset.y * aIndex);
	return elementPosition;
}