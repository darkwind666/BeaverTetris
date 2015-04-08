#pragma once

#include "cocos2d.h" 

class CocosNodesHelper
{
public:
	CocosNodesHelper(void);
	~CocosNodesHelper(void);

	static void addChildNodeToParentNodeWithKey(cocos2d::Node *aChildNode, cocos2d::Node *aParentNode, std::string aKey);
	static void addChildNodeToParentNodeWithZOrderFromKey(cocos2d::Node *aChildNode, cocos2d::Node *aParentNode, std::string aKey);
	static void addButtonToParentNodeWithKey(cocos2d::MenuItem *aButton, cocos2d::Node *aParentNode, std::string aKey);
};

