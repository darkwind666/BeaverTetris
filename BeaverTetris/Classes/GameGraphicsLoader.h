#pragma once

#include "ServiceInterface.h"
#include <string>

class GameGraphicsDataSource;

class GameGraphicsLoader : public ServiceInterface
{
public:
	GameGraphicsLoader(void);
	~GameGraphicsLoader(void);

	void setInitialGraphic();
	int getGraphicCount();
	void loadGraphicForIndex(int aIndex);

private:

	GameGraphicsDataSource *_gameGraphicsDataSource;

	void setGraphicWithFrameAndFile(std::string frame, std::string file);

};

