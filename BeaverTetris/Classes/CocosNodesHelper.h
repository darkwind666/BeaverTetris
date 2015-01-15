#pragma once

#include "cocos2d.h" 

class CocosNodesHelper
{
public:
	CocosNodesHelper(void);
	~CocosNodesHelper(void);

	static void addChildNodeToParentNodeWithKey(cocos2d::CCNode *aChildNode, cocos2d::CCNode *aParentNode, std::string aKey);
	static void addButtonToParentNodeWithKey(cocos2d::CCMenuItem *aButton, cocos2d::CCNode *aParentNode, std::string aKey);
};

