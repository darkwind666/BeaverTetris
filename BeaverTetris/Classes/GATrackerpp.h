#pragma once

#include <string>
#include <sstream>
#include <assert.h>
#include <thread>
#include "curl.h"

class GATrackerpp {

public:
    GATrackerpp(const std::string & trackinkId, const std::string & clientId, std::string appName, std::string appVersion);

    ~GATrackerpp();

	void sendEvent(const std::string & eventCategory, const std::string & eventAction);
    void sendEvent(const std::string & eventCategory, const std::string & eventAction, int value);
	void sendEvent(const std::string & eventCategory, const std::string & eventAction, std::string eventLabel);
	void sendEvent(const std::string & eventCategory, const std::string & eventAction, std::string eventLabel , int value);
    void sendAppView(const std::string & screenName);
	void sendStartAppView(const std::string & screenName, std::string shop, std::string language);
	void sendEndAppView(const std::string & screenName);

private:
    const std::string trackingId_;
    const std::string clientId_;
	int _handle;
	bool _onLine;
	std::string _appName;
	std::string _appVersion;

    void sendAnalytics(std::string const &payload);
};