#pragma once

#include <string>
#include "ServiceInterface.h"
#include <vector>

class GameGraphicsDataSource :public ServiceInterface
{
public:
	GameGraphicsDataSource(void);
	~GameGraphicsDataSource(void);

	std::string getInitialGraphic();
	std::string getInitialGraphicFrame();

	int getGraphicCount();
	std::string getGraphicForIndex(int aIndex);
	std::string getGraphicFrameForIndex(int aIndex);

private:

	std::vector<std::string> _graphicsKeys;

	std::vector<std::string> getGraphicKeys();

};
