#pragma once

#include <string>
#include "GameViewElementsDataSource.h"
#include "cocos2d.h"

class GameViewInformationFactory
{
public:
	GameViewInformationFactory(void);
	~GameViewInformationFactory(void);

	ViewElementInformation getViewInformationForKey(std::string aKey);

private:

	std::map <std::string , ViewElementInformation> _elementsInformation;

	std::map <std::string , ViewElementInformation> makeViewData(void);
	cocos2d::Vec2 getScreenCenter();

};

