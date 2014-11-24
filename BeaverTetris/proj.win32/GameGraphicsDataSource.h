#pragma once

#include <string>

class GameGraphicsDataSource
{
public:
	GameGraphicsDataSource(void);
	~GameGraphicsDataSource(void);

	std::string getInitialGraphic();
	int getGraphicCount();
	std::string getGraphicForIndex(int aIndex);

private:

	std::string _startGraphic;
	std::string *_graphics;
	int _graphicElementsCount;

};
