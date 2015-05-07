#include "ServiceLocator.h"

using namespace std;

static map <string, ServiceInterface*> _services;

ServiceInterface* ServiceLocator::getServiceForKey(string aKey) 
{
	ServiceInterface *service = NULL;
	map <string, ServiceInterface*>::iterator needServiceIterator;
	needServiceIterator = _services.find(aKey);
	if (needServiceIterator != _services.end())
	{
		service = _services[aKey];
	}
	return service;
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

void ServiceLocator::clean()
{
	map <string, ServiceInterface*>::iterator serviceIterator;
	for (serviceIterator = _services.begin(); serviceIterator != _services.end(); serviceIterator++)
	{
		delete serviceIterator->second;
	}
}
