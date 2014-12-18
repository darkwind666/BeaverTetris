#include "CurrentLevelDataSource.h"

using namespace std;

CurrentLevelDataSource::CurrentLevelDataSource(void)
{
	_observers = vector<CurrentLevelDataSourceObserver*>();
}


CurrentLevelDataSource::~CurrentLevelDataSource(void)
{
}

void CurrentLevelDataSource::playerChangeSelectedLevel(int aCurrentSelectedLevel)
{
	
	vector<CurrentLevelDataSourceObserver*>::iterator observersIterator;
	for (observersIterator = _observers.begin(); observersIterator != _observers.end(); observersIterator++)
	{
		CurrentLevelDataSourceObserver *observer = *observersIterator;
		observer->levelChanged();
	}

}

void CurrentLevelDataSource::addObserver(CurrentLevelDataSourceObserver *aCurrentLevelDataSourceObserver)
{
	_observers.push_back(aCurrentLevelDataSourceObserver);
}

void CurrentLevelDataSource::removeObserver(CurrentLevelDataSourceObserver *aCurrentLevelDataSourceObserver)
{
	vector<CurrentLevelDataSourceObserver*>::iterator observerIndex = find(_observers.begin(), _observers.end(), aCurrentLevelDataSourceObserver);
	_observers.erase(observerIndex);
}
