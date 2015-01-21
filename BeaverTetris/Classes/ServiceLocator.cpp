#include "ServiceLocator.h"

using namespace std;

static map <string, ServiceInterface*> _services;

ServiceInterface* ServiceLocator::getServiceForKey(string aKey) 
{
	return _services[aKey];
}

void ServiceLocator::setServiceForKey(ServiceInterface *service, string aKey) 
{

	map <string, ServiceInterface*>::iterator needServiceIterator;
	needServiceIterator = _services.find(aKey);
	if (needServiceIterator != _services.end())
	{
		delete needServiceIterator->second;
		_services.erase(needServiceIterator);
	}

	_services[aKey] = service;
}
