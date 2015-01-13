#pragma once

#include "ServiceInterface.h"
#include "ResourcesLoader.h"
#include <string>

class GameGraphicsDataSource;

class GameGraphicsLoader : public ServiceInterface , public ResourcesLoader
{
public:
	GameGraphicsLoader(void);
	~GameGraphicsLoader(void);

	void setInitialGraphic();

	virtual void loadResources();

private:

	GameGraphicsDataSource *_gameGraphicsDataSource;

	void setGraphicWithFrameAndFile(std::string frame, std::string file);
	int getGraphicCount();
	void loadGraphicForIndex(int aIndex);
};

