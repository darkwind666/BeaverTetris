#include "CocosNodesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"

using namespace cocos2d;

CocosNodesHelper::CocosNodesHelper(void)
{
}


CocosNodesHelper::~CocosNodesHelper(void)
{
}

void CocosNodesHelper::addChildNodeToParentNodeWithKey(CCNode *aChildNode, CCNode *aParentNode, std::string aKey)
{
	GameViewElementsDataSource *elementsData = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	int nodeZOrder = elementsData->getElementZOrderForKey(aKey);
	Vec2 nodePosition = elementsData->getElementPositionForKey(aKey);
	aChildNode->setPosition(nodePosition);
	aChildNode->setZOrder(nodeZOrder);
	aParentNode->addChild(aChildNode);
}

void CocosNodesHelper::addChildNodeToParentNodeWithZOrderFromKey(CCNode *aChildNode, CCNode *aParentNode, std::string aKey)
{
	GameViewElementsDataSource *elementsData = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	int nodeZOrder = elementsData->getElementZOrderForKey(aKey);
	aChildNode->setZOrder(nodeZOrder);
	aParentNode->addChild(aChildNode);
}

void CocosNodesHelper::addButtonToParentNodeWithKey(cocos2d::CCMenuItem *aButton, cocos2d::CCNode *aParentNode, std::string aKey)
{
	GameViewElementsDataSource *elementsData = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	int nodeZOrder = elementsData->getElementZOrderForKey(aKey);
	Vec2 nodePosition = elementsData->getElementPositionForKey(aKey);

	CCMenu *menuForButton = CCMenu::create();
	menuForButton->addChild(aButton);

	menuForButton->setPosition(nodePosition);
	menuForButton->setZOrder(nodeZOrder);
	aParentNode->addChild(menuForButton);
}