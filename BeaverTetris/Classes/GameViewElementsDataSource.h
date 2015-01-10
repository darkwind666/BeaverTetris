#pragma once

#include "ServiceInterface.h"
#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameViewInformationFactory;

class GameViewElementsDataSource :public ServiceInterface
{
public:
	GameViewElementsDataSource(void);
	~GameViewElementsDataSource(void);

	cocos2d::Vec2 getElementPositionForKey(std::string aKey);
	std::string getElementImageForKey(std::string aKey);
	int getElementZOrderForKey(std::string aKey);

private:

	GameViewInformationFactory *_gameViewInformationFactory;

};