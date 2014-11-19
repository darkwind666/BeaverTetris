#pragma once

#include <map>
#include "GameStructures.h"

using namespace std;

class Point;
class string;

class GameViewElementsDataSource
{
public:
	GameViewElementsDataSource(void);
	~GameViewElementsDataSource(void);

	Vec2 getElementPositionForKey(std::string aKey);
	std::string getElementImageForKey(std::string aKey);
	int getElementZOrderForKey(std::string aKey);

	void setViewStructureForKey(ViewElementInformation aElementInformation, std::string aKey);

private:

	map <std::string , ViewElementInformation> _elementsInformation;

};