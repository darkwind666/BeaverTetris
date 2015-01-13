#pragma once 

#include <vector>
#include "GameStructures.h"

class LoadingGameDataSource
{
public:
	LoadingGameDataSource(void);
	~LoadingGameDataSource(void);

	int getResourcesCount();
	int getResourceLoadingPercentForIndex(int aResourceIndex);
	void loadResouceForIndex(int aResourceIndex);

private:

	std::vector<ResoucesLoaderInformation> _loadersInformation;

	std::vector<ResoucesLoaderInformation> getLoadersInformation();

};

