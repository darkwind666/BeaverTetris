#pragma once

#include <string>
#include <map>

class GoogleAnalyticIndicatorsDataSource
{
public:
	GoogleAnalyticIndicatorsDataSource(void);
	~GoogleAnalyticIndicatorsDataSource(void);

	std::string getIndicatorNameForKey(std::string aKey);

private:

	std::map<std::string, std::string> _indicatorsNames;

	std::map<std::string, std::string> getIndicatorsNames();

};

