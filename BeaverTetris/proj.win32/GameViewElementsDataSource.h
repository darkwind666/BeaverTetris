#pragma once

#include <map>
#include <string>
#include "cocos2d.h"
#include "GameStructures.h"

class GameViewElementsDataSource
{
public:
	GameViewElementsDataSource(void);
	~GameViewElementsDataSource(void);

	cocos2d::Vec2 getElementPositionForKey(std::string aKey);
	std::string getElementImageForKey(std::string aKey);
	int getElementZOrderForKey(std::string aKey);

	void setViewStructureForKey(ViewElementInformation aElementInformation, std::string aKey);

private:

	std::map <std::string , ViewElementInformation> _elementsInformation;

};