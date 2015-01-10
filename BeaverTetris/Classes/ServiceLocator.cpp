#include "ServiceLocator.h"

static std::map <std::string, ServiceInterface*> _services;

ServiceInterface* ServiceLocator::getServiceForKey(std::string aKey) 
{
	return _services[aKey];
}

void ServiceLocator::setServiceForKey(ServiceInterface *service, std::string aKey) 
{
	_services[aKey] = service;
}
