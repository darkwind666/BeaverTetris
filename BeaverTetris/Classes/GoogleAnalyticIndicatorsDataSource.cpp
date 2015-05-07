#include "GoogleAnalyticIndicatorsDataSource.h"
#include "pugixml.hpp"
#include "GoogleAnalyticsKeys.h"

using namespace std;
using namespace pugi;

GoogleAnalyticIndicatorsDataSource::GoogleAnalyticIndicatorsDataSource(void)
{
	_indicatorsNames = getIndicatorsNames();
}


GoogleAnalyticIndicatorsDataSource::~GoogleAnalyticIndicatorsDataSource(void)
{
}

map<string, string> GoogleAnalyticIndicatorsDataSource::getIndicatorsNames()
{
	map<string, string> indicatorsNames;
	xml_document indicatorsFile;
	xml_parse_result result = indicatorsFile.load_file(analiticsIndicatorsFileKey.c_str());
	if (result)
	{
		xml_node indicators = indicatorsFile.child(analiticsIndicatorsKeys.c_str());
		xml_node indicator;
		for (indicator = indicators.first_child(); indicator; indicator = indicator.next_sibling())
		{
			string key = indicator.attribute(analiticsIndicatorTypeKey.c_str()).as_string();
			string value = indicator.attribute(analiticsIndicatorValueKey.c_str()).as_string();
			indicatorsNames[key] = value;
		}
	}
	return indicatorsNames;
}

string GoogleAnalyticIndicatorsDataSource::getIndicatorNameForKey(string aKey)
{
	return _indicatorsNames[aKey];
}
