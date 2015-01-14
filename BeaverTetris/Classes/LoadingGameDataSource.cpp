#include "LoadingGameDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "ResourcesLoader.h"
#include "GameGraphicsLoader.h"
#include "GameSoundLoader.h"
#include "GameDataLoader.h"
#include "GameLogicLoader.h"

const int graphicLoadingPercentage = 25;
const int soundLoadingPercentage = 25;
const int dataLoadingPercentage = 25;
const int logicLoadingPercentage = 25;

LoadingGameDataSource::LoadingGameDataSource(void)
{
	_loadersInformation = getLoadersInformation();
}

LoadingGameDataSource::~LoadingGameDataSource(void)
{
}

int LoadingGameDataSource::getResourcesCount()
{
	return _loadersInformation.size();
}

int LoadingGameDataSource::getResourceLoadingPercentForIndex(int aResourceIndex)
{
	ResoucesLoaderInformation loaderInformation = _loadersInformation[aResourceIndex];
	return loaderInformation.loadPercentage;
}

void LoadingGameDataSource::loadResouceForIndex(int aResourceIndex)
{
	ResoucesLoaderInformation loaderInformation = _loadersInformation[aResourceIndex];
	loaderInformation.resourcesLoader->loadResources();
}

vector<ResoucesLoaderInformation> LoadingGameDataSource::getLoadersInformation()
{
	vector<ResoucesLoaderInformation> loadersInformation;

	ResoucesLoaderInformation graphicLoader;
	graphicLoader.loadPercentage = graphicLoadingPercentage;
	graphicLoader.resourcesLoader = (GameGraphicsLoader*)ServiceLocator::getServiceForKey(gameGraphicsLoaderKey);

	ResoucesLoaderInformation soundLoader;
	soundLoader.loadPercentage = soundLoadingPercentage;
	soundLoader.resourcesLoader = new GameSoundLoader();

	ResoucesLoaderInformation dataLoader;
	dataLoader.loadPercentage = dataLoadingPercentage;
	dataLoader.resourcesLoader = new GameDataLoader();

	ResoucesLoaderInformation logicLoader;
	logicLoader.loadPercentage = logicLoadingPercentage;
	logicLoader.resourcesLoader = new GameLogicLoader();

	loadersInformation.push_back(graphicLoader);
	loadersInformation.push_back(soundLoader);
	loadersInformation.push_back(dataLoader);
	loadersInformation.push_back(logicLoader);

	return loadersInformation;
}