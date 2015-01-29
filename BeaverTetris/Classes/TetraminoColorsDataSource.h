#pragma once

#include "cocos2d.h"
#include <string>
#include <map>

class TetraminoColorsDataSource
{
public:
	TetraminoColorsDataSource(void);
	~TetraminoColorsDataSource(void);

	cocos2d::Color3B getColorForKey(std::string aKey);

private:

	std::map<std::string, cocos2d::Color3B> _tetraminosColors;

	std::map<std::string, cocos2d::Color3B> getTetraminosColors();

};

