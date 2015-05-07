#pragma once

#include <string>
#include <map>
#include "ServiceInterface.h"

class ServiceLocator
{
public:

	static ServiceInterface* getServiceForKey(std::string aKey);
	static void setServiceForKey(ServiceInterface *service, std::string aKey);
	static void clean();

};